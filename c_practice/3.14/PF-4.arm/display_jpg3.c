#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "common.h"

extern int *status_p;
static void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int display_line(u16_t *buf32, fb_info fb_inf, int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int inc = ((dy * dx > 0) ? 1 : -1);
    if (abs(dx) > abs(dy))
    {
        if(dx < 0)
        {
            swap(&x1, &x2);
            swap(&y1, &y2);
            dx = -dx;
            dy = -dy;
        }
        dy = abs(dy);
        int p = 2 * dy - dx;
        while (x1 <= x2)
        {
            fb_pixel(fb_inf,x1, y1, buf32[x1+y1*fb_inf.w]);
            x1++;
            if (p < 0)
                p += 2 * dy;
            else
            {
                p += 2 * (dy - dx);
                y1 += inc;
            }
        }
    }
    else
    {
        if(dy < 0)
        {
            swap(&x1, &x2);
            swap(&y1, &y2);
            dx = -dx;
            dy = -dy;
        }
        dx = abs(dx);
        int p = 2 * dx - dy;
        while (y1 <= y2)
        {
            //fb_one_piexl(x1, y1, color);
            fb_pixel(fb_inf,x1, y1, buf32[x1+y1*fb_inf.w]);
            y1++;
            if (p < 0)
                p += 2 * dx;
            else
            {
                p += 2 * (dx - dy);
                x1 += inc;
            }
        }
    }

    return 0;
}
    

int display_box(const char *filename, fb_info fb_inf, fb_info fb_xin)
{

    fb_info jpeg_inf;
    fb_info fb_inff = fb_xin;

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inff, jpeg_inf);
    u16_t *buf32 = rgb24to16(scale_buf, fb_inff);

    int x = fb_inf.h/2, y = fb_inf.h/2;
    int x1 = fb_inf.w-fb_inf.h/2, y1 = fb_inf.h/2;
    int x2 = fb_inf.h/2, y2 = fb_inf.h/2;
    int x3 = fb_inf.w-fb_inf.h/2, y3 = fb_inf.h/2;
    int x4 = fb_inf.h/2, y4=0, x5 = 0;
    int x6 = fb_inf.w-fb_inf.h/2, y6 = 0, x7 = fb_inf.w;
    int x8 = fb_inf.h/2, y8 = fb_inf.h-1, x9 = 0;
    int x10 = fb_inf.w - fb_inf.h/2, y10 = fb_inf.h - 1, x11 = fb_inf.w;

    while((x4<=fb_inf.w/2) && (y4<=fb_inf.h/2)) 
    {
        if(x>0 && y>0)
        {
            display_line(buf32, fb_inf, x, 0, 0, y);
            y--;
            x--;

            display_line(buf32, fb_inf, x1, 0, fb_inf.w, y1);
            y1--;
            x1++;

            display_line(buf32, fb_inf, 0, y2, x2, fb_inf.h);
            y2++;
            x2--;

            display_line(buf32, fb_inf, x3, fb_inf.h, fb_inf.w, y3);
            y3+=1;
            x3+=1;
        }

            display_line(buf32, fb_inf, x4, y4, x5, fb_inf.h/2);
            x5++;
            if(x4 == fb_inf.w/2)
            {
                x4 = fb_inf.w/2;
                y4++;
            }
            else
                x4++;

            display_line(buf32, fb_inf, x6, y6, x7, fb_inf.h/2);
            x7--;
            if(x6 == fb_inf.w/2)
            {
                x6 = fb_inf.w/2;
                y6++;
            }
            else
                x6--;

            display_line(buf32, fb_inf, x8, y8, x9, fb_inf.h/2);
            x9++;
            if(x8 == fb_inf.w/2)
            {
                x8 = fb_inf.w/2;
                y8--;
            }
            else
                x8++;

            display_line(buf32, fb_inf, x10, y10, x11, fb_inf.h/2);
            x11--;
            if(x10 == fb_inf.w/2)
            {
                x10 = fb_inf.w/2;
                y10--;
            }
            else
                x10--;
        if(*status_p == 0) goto biaoshan1;
        usleep(10);
    }
    biaoshan1: free(buf24);
    free(scale_buf);
    free(buf32);

    return 0;
}

int display_v_up(const char *filename, fb_info fb_inf, fb_info fb_xin)
{

    fb_info jpeg_inf;
    fb_info fb_inff = fb_xin;
    int x1 = fb_inf.w/2, y1 = fb_inf.h, x2 = fb_inf.w/2, y2 = fb_inf.h; 
    int x3 = fb_inf.w/2, y3 = fb_inf.h-1, x4 = fb_inf.w/2, y4 = fb_inf.h-1; 

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inff, jpeg_inf);
    u16_t *buf32 = rgb24to16(scale_buf, fb_inff);
    

    while(y1>0) 
    {
            display_line(buf32, fb_inf, x1, y1, x2, y2);

            if(x1 == fb_inf.w-1)
            {
                x1 = fb_inf.w-1;
                y1--;
            }
            else
                x1++;

            if(y2 == 0)
            {
                y2=0;
                x2++;
            }
            else
                y2--;
                
            display_line(buf32, fb_inf, x3, y3, x4, y4);

            if(x3 == 0)
            {
                x3 = 0;
                y3--;
            }
            else
                x3--;

            if(y4 == 0)
            {
                y4=0;
                x4--;
            }
            else
                y4--;
            usleep(2);
            if(*status_p == 0) goto biaoshan2;
    }
    biaoshan2: free(buf24);
    free(scale_buf);
    free(buf32);

    return 0;
}

int display_zig(const char *filename, fb_info fb_inf, fb_info fb_xin)
{
    fb_info jpeg_inf;
    fb_info fb_inff = fb_xin;
    int y[7],y1[7];
    int x1, x2, x3, x4, y20, y11, y40, y31, y60, y51, y7, y71;
    int i = 0;
    x1 = x3 =fb_inf.w/2 - 34,  x2 = x4 = fb_inf.w/2 + 34; 
    y20 =(fb_inf.h/7+1)*2; y11 =(fb_inf.h/7+1)*1;
    y40 = (fb_inf.h/7+1)*4; y31 = (fb_inf.h/7+1)*3; 
    y60 = (fb_inf.h/7)*6; y51 = (fb_inf.h/7)*5;
    y7 = y71 = fb_inf.h - 1;

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inff, jpeg_inf);
    u16_t *buf32 = rgb24to16(scale_buf, fb_inff);

    for(i=0; i<7; i++)
    {
        if(i<=4)
        {
            y[i] = (fb_inf.h/7+1)*i;
            y1[i] = (fb_inf.h/7+1)*i;
        }
        else
        {
            y[i] = (fb_inf.h/7)*i;
            y1[i] = (fb_inf.h/7)*i;
        }
    }

    while(x1<fb_inf.w)
    {
        display_line(buf32, fb_inf, x1, y[1], x2, y[0]);
        display_line(buf32, fb_inf, x1, y[1], x2, y[2]);
        display_line(buf32, fb_inf, x1, y[3], x2, y20);
        display_line(buf32, fb_inf, x1, y[3], x2, y[4]);
        display_line(buf32, fb_inf, x1, y[5], x2, y40);
        display_line(buf32, fb_inf, x1, y[5], x2, y[6]);
        display_line(buf32, fb_inf, x2, y60, x1, y7);

        display_line(buf32, fb_inf, x3, y1[1], x4, y1[0]);
        display_line(buf32, fb_inf, x3, y11, x4, y1[2]);

        display_line(buf32, fb_inf, x3, y1[3], x4, y1[2]);
        display_line(buf32, fb_inf, x3, y31, x4, y1[4]);

        display_line(buf32, fb_inf, x3, y1[5], x4, y1[4]);
        display_line(buf32, fb_inf, x3, y51, x4, y1[6]);

        display_line(buf32, fb_inf, x4, y1[6], x3, y71);
        if(x3 == 0)
        {
            x3 = 0;
            y11++;
            y31++;
            y1[1]--;
            y1[3]--;
            //y7--;
            y1[5]--;
            y51++;
            y71--;
            x4--;
        }
        else
        {
            x3--;
            x4--;
        }
        if(x2 == fb_inf.w-1)
        {
            x2 = fb_inf.w - 1;
            y[0]++;
            y20++;
            y40++;
            y[2]--;
            y[4]--;
            //y7--;
            y[6]--;
            y60++;
            x1++;
        }
        else
        {
            x1++;
            x2++;
        }
        usleep(10);
        if(*status_p == 0) goto biaoshan3;
        
    }
    biaoshan3:
    free(buf24);
    free(scale_buf);
    free(buf32);
    return 0;
}
