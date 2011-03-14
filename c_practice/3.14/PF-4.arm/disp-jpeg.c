#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <pthread.h>
#include "common.h"

#define DEBUG 0
#if DEBUG
#endif
extern pthread_mutex_t mice_lock;
int display_jpeg_dj(char *filename, fb_info fb_in)
{

    fb_info jpeg_inf;

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_in, jpeg_inf);
    u16_t *buf32 = rgb24to16(scale_buf, fb_in);

    int i, j;
    for(i = 0; i < fb_in.h; ++i){
        for (j = 0; j < fb_in.w; ++j){
            fb_pixel(fb_in, j, i, buf32[j +i* fb_in.w]);
        }
    }

    free(buf24);
    free(scale_buf);
    free(buf32);

    return 0;
}
typedef struct{
    int pos_x;
    int pos_y;
}pos_start_t;
extern int position_id[];
extern char *pic_pool[];
extern fb_info fb_inf;
extern int m_x, m_y;
u16_t * decode_small_jpeg(char *filename, fb_info fb_in)
{
    fb_info jpeg_inf;

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_in, jpeg_inf);
    u16_t *buf32 = rgb24to16(scale_buf, fb_in);
    free(buf24);
    free(scale_buf);
    
    return buf32;
}
int display_one_small_jpeg(u16_t *buf32, fb_info fb_in, int x, int y)
{


    int i, j;
    for(i = 0; i < fb_in.h/3; ++i){
        for (j = 0; j < fb_in.w/3; ++j){
            fb_pixel(fb_in, j+x, i+y, buf32[j*3 +i*3* fb_in.w]);
        }
    }

    free(buf32);

    return 0;
}
int display_mid_jpeg(char *filename, fb_info fb_in, int x, int y)
{

    fb_info jpeg_inf;

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_in, jpeg_inf);
    u16_t *buf32 = rgb24to16(scale_buf, fb_in);

    int i, j;
    for(i = 0; i < fb_in.h/1.5; ++i){
        for (j = 0; j < fb_in.w/1.5; ++j){
            fb_pixel(fb_in, j+x, i+y, buf32[(int)(j*1.5) +(int)(i*1.5)* fb_in.w]);
        }
    }

    free(buf24);
    free(scale_buf);
    free(buf32);

    return 0;
}

int disp_four_pic(int start_num)
{
    int i = start_num;
    u16_t *buf_p[4];
    pos_start_t small_pos[4] = {
        {140, 68}, {407, 68}, {140, 228}, {407, 228}
    };


    for (; i < 4+start_num; i++) 
    {
        buf_p[i-start_num]= decode_small_jpeg(pic_pool[i], fb_inf);
    }
    i = start_num;
            pthread_mutex_lock(&mice_lock);
    for (; i < 4+start_num; i++) 
    {
        position_id[i-start_num] = i;
        display_one_small_jpeg(buf_p[i-start_num], fb_inf, small_pos[i-start_num].pos_x,small_pos[i-start_num].pos_y);
    }
    if(m_x>140&&m_x<407+267-17&&m_y>68&&m_y<228+160)
        {
            fb_drawcursor(fb_inf, m_x, m_y);
        }
            pthread_mutex_unlock(&mice_lock);

    return 0;
} 
