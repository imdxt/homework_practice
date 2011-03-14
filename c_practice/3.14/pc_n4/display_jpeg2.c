#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "common.h"
extern int *status_p;
void swap(int *a,int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int fb_line222(u32_t *buf32, fb_info fb_inf,int x1,int y1,int x2,int y2)
{
    int dx = x2-x1;
    int dy = y2-y1;
    int inc = ((dx*dy>0) ? 1:-1);
    int p = 0;

	if(abs(dx) > abs(dy))
	{
		if(dx < 0)
		{
			swap(&x1, &x2);
			swap(&y1, &y2);
			dx = -dx;
			dy = -dy;
		}

		dy = abs(dy);
		p=2*dy-dx;
		while(x1 <= x2)
		{
			fb_pixel(fb_inf, x1, y1, buf32[x1 + y1 * fb_inf.w]);
			x1++;
			if(p < 0)
			{
				p += 2*dy;
			}
			else
			{
				p += 2*(dy-dx);
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
		p=2*dx-dy;

		while(y1 <= y2)
		{
			fb_pixel(fb_inf, x1, y1, buf32[x1 + y1 * fb_inf.w]);
			y1++;
			if(p < 0)
			{
				p += 2*dx;
			}
			else
			{
				p += 2*(dx-dy);
				x1 += inc;
			}
		}

	}
	return 0;

}
int fb_line2(const char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int i,j;
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    for(i = 0;i < 32 ;i++)
    {
        for(j = 0;j < 32;j++)
        {
            if(*status_p == 0) goto biao1;
            if(i < 24)
                fb_line222(buf32, fb_inf,1023,i + j*24,0,767 - i - j*24);
            fb_line222(buf32, fb_inf,i + j*32, 0 ,1023 - i - j*32,767);
        }
               usleep(10);

    }
    biao1: free(buf24);
    free(scale_buf);
    free(buf32);
    return 0;
}
int fb_line1(const char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    int i = 5000, j;
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    for(j = fb_inf.h - 2; j >= 0 ; j--)
    {
            if(*status_p == 0)break;
        fb_line222(buf32, fb_inf,fb_inf.w/2-1,fb_inf.h - 1,fb_inf.w,j);
        while(i--);
        i = 5000;
    }
    for(j = fb_inf.w-1; j > 0; j--)
    {
            if(*status_p == 0)break;
        fb_line222(buf32, fb_inf,fb_inf.w/2-1,fb_inf.h - 1,j,0);
        while(i--);
        i = 5000;
    }
    for(j = 0; j < fb_inf.h - 1 ; j++)
    {
            if(*status_p == 0)break;
        fb_line222(buf32, fb_inf,fb_inf.w/2-1,fb_inf.h - 1,0,j);
        while(i--);
        i = 5000;
    }
    free(buf24);
    free(scale_buf);
    free(buf32);
    return 0;
}
int fb_line4(const char *filename, fb_info fb_inf)
{
    fb_info jpeg_inf;
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    int i = 0,m = fb_inf.h;
    int b[1024] = {0};
    srand(time(NULL));
    while( m--)
    {
        while(1)
        {
        i = rand()%fb_inf.h;
        if(b[i] == 1)
        {
            continue;
        }
        else
        {
            b[i] = 1;
            break;
        }
        }
        fb_line222(buf32, fb_inf,0,i ,fb_inf.w,i );
        fb_line222(buf32, fb_inf,i,0 ,i,fb_inf.h - 1 );
        if(*status_p == 0) goto dong03;
        //usleep(100);
    }
    dong03:
    free(buf24);
    free(scale_buf);
    free(buf32);
    return 0;
}
/*int display_scale1(char *filename, fb_info fb_inf)
{
    if(jpeg_w >= fb_inf.w || jpeg_h >= fb_inf.h || jpeg_w < 0 || jpeg_h <0)
    {
        perror("the jpeg_w or jpeg_h is error!\n");
        exit(1);
    }

	fb_info jpeg_inf;

    fb_info fb_inff;
    fb_inff.h = jpeg_h;
    fb_inff.w = jpeg_w;
    fb_inff.bpp = fb_inf.bpp;
    fb_inff.fbmem = fb_inf.fbmem;
	
	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inff, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inff);

	int i, j,m,n;
    for(i =50,n = 0,m = 0; i < fb_inff.w+50; i = i + 1,n = n + 4,m++){
        for (j = 0; j < fb_inff.w; j++){
            if(*status_p == 0)goto biao;
                fb_line222(buf32, fb_inff,j ,767,i,fb_inf.h);
        }
    }

biao:	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}*/
