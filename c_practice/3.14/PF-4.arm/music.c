#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/soundcard.h>
#include <sys/ioctl.h>
#include <string.h>
#include "mad.h"
#include "common.h"

extern int *play_flag;
int soundfd;
char mp3_fd[3];
struct buffer 
{
    unsigned char const *start;
    unsigned long length;
};
char *mp3_name[3] = {"再回首", "小三", "明天会更好"};

int play(int *p) 
{
    struct stat file;
    void *address;
    int num;
    num = *p;
    //int n = 0;

    if((mp3_fd[num] = open(mp3_name[num], O_RDONLY)) < 0)
    {
        perror("open 1");
        exit(1);
    }
    fstat(mp3_fd[num], &file);
    address = mmap(0, file.st_size, PROT_READ, MAP_SHARED,mp3_fd[num], 0);      
    decode(address, file.st_size);
    if(munmap(address, file.st_size) == -1)
        perror("mumap");
    close(mp3_fd[num]); 
    return num;
}

int writedsp(int c)
{
    return write(soundfd, (char *)&c, 1);
}

void set_dsp(void)
{
    int format = AFMT_S16_LE;
    int channels = 1;
    unsigned int rate = 44100;

    if((soundfd = open("/dev/dsp", O_RDWR)) < 0)
    {
        perror("open dsp");
        exit(1);
    }

    ioctl(soundfd, SNDCTL_DSP_SETFMT, &format);
    ioctl(soundfd, SNDCTL_DSP_SYNC, 0);
    ioctl(soundfd, SNDCTL_DSP_CHANNELS, &channels);
    ioctl(soundfd, SNDCTL_DSP_SPEED,&rate);
    //ioctl(soundfd, SOUND_PCM_WRITE_CHANNELS, &channels);
    //ioctl(soundfd, SOUND_PCM_WRITE_RATE, &rate);
}


/*
 * This is the input callback. The purpose of this callback is to (re)fill
 * the stream buffer which is to be decoded. In this example, an entire file
 * has been mapped into memory, so we just call mad_stream_buffer() with the
 * address and length of the mapping. When this callback is called a second
 * time, we are finished decoding.
 */

static enum mad_flow input(void *data, struct mad_stream *stream)
{
    struct buffer *buffer = data;

    if (!buffer->length)
        return MAD_FLOW_STOP;

    mad_stream_buffer(stream, buffer->start, buffer->length);

    buffer->length = 0;

    return MAD_FLOW_CONTINUE;
}

/*
 * The following utility routine performs simple rounding, clipping, and
 * scaling of MAD's high-resolution samples down to 16 bits. It does not
 * perform any dithering or noise shaping, which would be recommended to
 * obtain any exceptional audio quality. It is therefore not recommended to
 * use this routine if high-quality output is desired.
 */

static inline signed int scale(mad_fixed_t sample)
{
    /* round */
    sample += (1L << (MAD_F_FRACBITS - 16));

    /* clip */
    if (sample >= MAD_F_ONE)
        sample = MAD_F_ONE - 1;
    else if (sample < -MAD_F_ONE)
        sample = -MAD_F_ONE;

    /* quantize */
    return sample >> (MAD_F_FRACBITS + 1 - 16);
}

/*
 * This is the output callback function. It is called after each frame of
 * MPEG audio data has been completely decoded. The purpose of this callback
 * is to output (or play) the decoded PCM audio.
 */

enum mad_flow output(void *data, struct mad_header const *header, struct mad_pcm *pcm)
{
    unsigned int nchannels, nsamples;
    mad_fixed_t const *left_ch, *right_ch;
    //unsigned int rate = 44100;

    /* pcm->samplerate contains the sampling frequency */

    //rate = pcm->samplerate;  
    nchannels = pcm->channels;
    nsamples  = pcm->length;
    left_ch   = pcm->samples[0];
    right_ch  = pcm->samples[1];

    //if(rate != prerate)
    //{
    //ioctl(soundfd, SNDCTL_DSP_SPEED, &rate);
    //prerate = rate;
    //}

    while (nsamples--)
    {
        signed int sample;

        /* output sample(s) in 16-bit signed little-endian PCM */

        while(*play_flag == 1)
        {
            usleep(1000);
        }
        sample = scale(*left_ch++);
        writedsp((sample >> 0) & 0xff);
        writedsp((sample >> 8) & 0xff);

        //if (nchannels == 2)
        //{
        //sample = scale(*right_ch++);
        //writedsp((sample >> 0) & 0xff);
        //writedsp((sample >> 8) & 0xff);
        //}
    }

    return MAD_FLOW_CONTINUE;
}

static enum mad_flow error(void *data, struct mad_stream *stream, struct mad_frame *frame)
{
    //struct buffer *buffer = data;

    //fprintf(stderr, "decoding error 0x%04x (%s) at byte offset %u\n", stream->error, mad_stream_errorstr(stream), stream->this_frame - buffer->start);

    /* return MAD_FLOW_BREAK here to stop decoding (and propagate an error) */

    return MAD_FLOW_CONTINUE;
}

/*
 * This is the function called by main() above to perform all the
 * decoding. It instantiates a decoder object and configures it with the
 * input, output, and error callback functions above. A single call to
 * mad_decoder_run() continues until a callback function returns
 * MAD_FLOW_STOP (to stop decoding) or MAD_FLOW_BREAK (to stop decoding and
 * signal an error).
 */

int decode(unsigned char const *start, unsigned long length)
{
    struct buffer buffer;
    struct mad_decoder decoder;
    int result;

    /* initialize our private message structure */

    buffer.start  = start;
    buffer.length = length;

    /* configure input, output, and error functions */

    mad_decoder_init(&decoder, &buffer, input, 0 /* header */, 0 /* filter */, output, error, 0 /* message */);

    /* start decoding */

    result = mad_decoder_run(&decoder, MAD_DECODER_MODE_SYNC);

    /* release the decoder */

    mad_decoder_finish(&decoder);

    return result;
}
