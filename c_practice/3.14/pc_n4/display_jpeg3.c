#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "common.h"

//#define fb_line(j) memcpy(fb_inf.fbmem+(fb_inf.w*(j)*fb_inf.bpp/8),&buf32[(j)*fb_inff.w],fb_inff.w*fb_inff.bpp/8)

#define fb_line(j) memcpy(fb_inf.fbmem+(fb_inf.w*(j)*fb_inf.bpp/8),&buf32[(j)*fb_inf.w],fb_inf.w*fb_inf.bpp/8)
extern int *status_p;
typedef struct 
{
    int x;
    int y;
}point_t;

int display_flash1(const char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    int i, j;
    int k = fb_inf.w*fb_inf.h;
    int b[fb_inf.w][fb_inf.h];
    bzero(b, fb_inf.w*fb_inf.h*sizeof(int));
    srand(time(NULL));
    while(k--)
    {   
        while(1)
        {
            i = rand() % fb_inf.w;
            j = rand() % fb_inf.h;
            if(b[i][j] == 1)
                continue;
            else
            {
                b[i][j] = 1;
                break;
            }
        }   
            fb_pixel(fb_inf,i,j,buf32[i + j*fb_inf.w]);
            if(*status_p == 0)
            goto biaosuiji;
    }
biaosuiji:
    free(buf24);
    free(scale_buf);
    free(buf32);

    return 0;
}

int display_flash2(const char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    int i, j;
    point_t p, q;
    for(i=0; i<fb_inf.w; i=i+2)
    {
        for(j=0; j<fb_inf.h; j=j+2)
        {
            p.x = (fb_inf.w - i);
            p.y = j;
            q.x = i + 1;
            q.y = j + 1;
            fb_pixel(fb_inf, p.x, p.y, buf32[j*fb_inf.w + (fb_inf.w - i)]);
            fb_pixel(fb_inf, q.x, q.y, buf32[j*fb_inf.w + i]);
            if(*status_p == 0) goto dong08;
        }
        usleep(4);
    }
    for(i=0; i<fb_inf.w/2+1; i = i + 1)
    {
        for(j=0; j<fb_inf.h; j= j + 1)
        {
            p.x = (fb_inf.w - 1 - i);
            p.y = j;
            q.x = i;
            q.y = j;
            fb_pixel(fb_inf, p.x, p.y, buf32[j*fb_inf.w + (fb_inf.w - i)]);
            fb_pixel(fb_inf, q.x, p.y, buf32[j*fb_inf.w + i]);
            if(*status_p == 0) goto dong08;
        }
        usleep(3);
    }
    dong08:
    free(buf24);
    free(scale_buf);
    free(buf32);

    return 0;
}

int display_midtoside(const char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    int i,j = 50000,m = 5;
    for(i=0; i<=fb_inf.h/2-1; i++)
    {
        fb_line(fb_inf.h/2 - 1 - i);
       
        fb_line(fb_inf.h/2+i);
        while(m--)
        {
            while(j--);
        j = 50000;
        }
        m = 5;
        if(*status_p == 0) goto dong05;
    }
dong05:
    free(buf24);
    free(scale_buf);
    free(buf32);

    return 0;
}


int display_xie1(const char *filename, fb_info fb_inf)
{

    fb_info jpeg_inf;
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    int i, j, n, m;

    
    for(i=0, j=0; i<= fb_inf.h || j<= fb_inf.w; i= i + 6, j = j + 8)
    {
        for(n=0; n<i; n++)
            for(m=0; m<j; m++)
            {
            if(*status_p == 0) goto biao2;
                
                fb_pixel(fb_inf, m, n, buf32[fb_inf.w * (fb_inf.h -i + n) + fb_inf.w - j + m]);
                
            }
    }
    biao2:
    free(buf24);
    free(scale_buf);
    free(buf32);

    return 0;
}

int display_four(const char *filename, fb_info fb_inf)
{

    fb_info jpeg_inf;

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    int i, j, n, m;

    for(i=0, j=0; i<=fb_inf.h/2 || j<=fb_inf.w/2; i= i + 6, j = j + 8)
    {
        for(n=0; n<=i; n++)
        {
            for(m=0; m<=j; m++)
            {
            if(*status_p == 0) goto biao3;
                fb_pixel(fb_inf, m, n, buf32[fb_inf.w * (fb_inf.h/2 -i + n) + fb_inf.w/2 - j + m]);
                fb_pixel(fb_inf, m, fb_inf.h - n - 1, buf32[fb_inf.w * (fb_inf.h/2 + i - n) + fb_inf.w/2 - j + m]);

                fb_pixel(fb_inf, fb_inf.w - m, n, buf32[fb_inf.w * (fb_inf.h/2 -i + n) + fb_inf.w/2 + j - m]);
                fb_pixel(fb_inf, fb_inf.w - m, fb_inf.h - n - 1, buf32[fb_inf.w * (fb_inf.h/2 +i -n) + fb_inf.w/2 +j - m]);
            }
        }
    }
    biao3:
    free(buf24);
    free(scale_buf);
    free(buf32);

    return 0;
}

