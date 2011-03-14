
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "common.h"

#define DEBUG 0
#if DEBUG
#endif
extern int *status_p;


int display_jpeg2(char *filename, fb_info fb_inf)//si zhou xiang zhong jian
{

	fb_info jpeg_inf;
	
	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j,n = 0;
	for(i = 0; i < fb_inf.h/2; i++ ){
		    for (j = i; j < fb_inf.w - i; ++j){
			    fb_pixel(fb_inf, j, i, buf32[j + i * fb_inf.w]);
			    fb_pixel(fb_inf, j, fb_inf.h - i - 1, buf32[j + (fb_inf.h - i - 1) * fb_inf.w]);
		    }   
            if(i > fb_inf.w/4)
            {
                n = n + 1;
            }
            for (j = i; j < fb_inf.h - i-1; ++j){
                fb_pixel(fb_inf, i + n, j, buf32[i + n + j * fb_inf.w]);
                fb_pixel(fb_inf, fb_inf.w - i - n, j , buf32[fb_inf.w - i - n + j * fb_inf.w]);
            }
            for (j = fb_inf.w/4; j < fb_inf.h - i-1; ++j){
                fb_pixel(fb_inf, i + n + 1, j, buf32[i + n + 1 + j * fb_inf.w]);
                fb_pixel(fb_inf, fb_inf.w - i - n - 1, j , buf32[fb_inf.w - i - n -1 + j * fb_inf.w]);
            }
            usleep(1);
	}

	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}
int display_jpeg12(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;
	
	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j, n ;
    
	for(i = 0; i < fb_inf.h-1; ++i){
        for(n = 0; n < 80; n = n + 2)
		for (j = 0; j < 16; j++){
            fb_pixel(fb_inf, j + 16*n, i, buf32[j + 16*n + i * fb_inf.w]);
		}
	
    for(n = 1; n <= 80; n=n+2)
		for (j = 0; j < 16 ; j++){
            fb_pixel(fb_inf, j + 16*n, fb_inf.h - i - 1, buf32[j + 16*n + (fb_inf.h - i - 1) * fb_inf.w]);
		}
    usleep(1);
	}
	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}
int display_jpeg13(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;
	
	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j, n ,m;
    
	for(i = 0; i <= fb_inf.h; i = i + 4){
        for(m = i-1; m > 0; m--)
            for(n = 0; n < 80; n = n + 2)
		        for (j = 0; j < 16; j++){
			        fb_pixel(fb_inf, j + 16*n, m - 1, buf32[j + 16*n + (fb_inf.h - i + m - 1) * fb_inf.w]);
			        fb_pixel(fb_inf, j + 16*(n+1), fb_inf.h - m , buf32[j + 16*(n+1) + (i - m)* fb_inf.w]);
                    if(*status_p == 0)goto biao11;
		}
	}
   biao11: 

	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}
int display_jpeg14(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;
	
	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j ,m;
    
	for(i = fb_inf.h - 300; i <= fb_inf.h; i = i + 100){ //down
        for(m = i; m > 0; m--)
		        for (j = 0; j < fb_inf.w; j++){
			        fb_pixel(fb_inf, j , m-1 , buf32[j + (fb_inf.h - i + m - 1) * fb_inf.w]);
		}
	}
    //for(i = fb_inf.h; i > fb_inf.h - 100; i = i - 20){  //up
    //for(m = i; m > 0; m--){
    //for (j = 0; j < fb_inf.w; j++){
    //fb_pixel(fb_inf, j , m , buf32[j + (fb_inf.h - i + m - 1) * fb_inf.w]);
    //if(m > i - 20)
    //fb_pixel(fb_inf, j , m, 0);
    //}
    //}
    //}
    //for(i = fb_inf.h - 100; i <= fb_inf.h ; i = i + 20){  //down
    //for(m = i; m > 0; m--){
    //for (j = 0; j < fb_inf.w; j++){
    //fb_pixel(fb_inf, j , m , buf32[j + (fb_inf.h - i + m - 1) * fb_inf.w]);
    //}
    //}
    //}  
	for(i = fb_inf.h; i > fb_inf.h - 60; i = i - 20){  //up
        for(m = i; m > 0; m--){
		        for (j = 0; j < fb_inf.w; j++){
			        fb_pixel(fb_inf, j , m -1, buf32[j + (fb_inf.h - i + m - 1) * fb_inf.w]);
                    if(m > i - 20)
                        fb_pixel(fb_inf, j , m-1, 0);
		        }
        }
	}
	for(i = fb_inf.h - 60; i <= fb_inf.h ; i = i + 20){  //down
        for(m = i; m > 0; m--){
		        for (j = 0; j < fb_inf.w; j++){
			        fb_pixel(fb_inf, j , m-1 , buf32[j + (fb_inf.h - i + m - 1) * fb_inf.w]);
		        }
        }
    }
	for(i = fb_inf.h; i > fb_inf.h - 40; i = i - 20){  //up
        for(m = i; m > 0; m--){
		        for (j = 0; j < fb_inf.w; j++){
			        fb_pixel(fb_inf, j , m-1 , buf32[j + (fb_inf.h - i + m - 1) * fb_inf.w]);
                    if(m > i - 20)
                        fb_pixel(fb_inf, j , m-1, 0);
		        }
        }
	}
	for(i = fb_inf.h - 40; i <= fb_inf.h ; i = i + 20){  //down
        for(m = i; m > 0; m--){
		        for (j = 0; j < fb_inf.w; j++){
			        fb_pixel(fb_inf, j , m-1 , buf32[j + (fb_inf.h - i + m - 1) * fb_inf.w]);
		        }
        }
    }
	for(i = fb_inf.h; i > fb_inf.h - 20; i = i - 20){  //up
        for(m = i; m > 0; m--){
		        for (j = 0; j < fb_inf.w; j++){
			        fb_pixel(fb_inf, j , m-1 , buf32[j + (fb_inf.h - i + m - 1) * fb_inf.w]);
                    if(m > i - 20)
                        fb_pixel(fb_inf, j , m-1, 0);
		        }
        }
	}
	for(i = fb_inf.h - 20; i <= fb_inf.h ; i = i + 20){  //down
        for(m = i; m > 0; m--){
		        for (j = 0; j < fb_inf.w; j++){
			        fb_pixel(fb_inf, j , m-1 , buf32[j + (fb_inf.h - i + m - 1) * fb_inf.w]);
		        }
        }
    }

	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}
int display_jpeg111(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;
	
	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j, n ,m;
    for(i = fb_inf.h - 10; i < fb_inf.h; i++ ){
        for(m = i; m > 0; m-- )
            for(n = 0; n < fb_inf.w/2; n = n + 2)
                for (j = 0; j < 2; ++j){
                    fb_pixel(fb_inf, j + 2*n, m, buf32[j + 2*n + (fb_inf.h - i + m - 1 ) * fb_inf.w]);
                    fb_pixel(fb_inf, j + 2*(n+1) , fb_inf.h - m - 1, buf32[j + 2*(n+1) + (i - m)* fb_inf.w]);
                }
    }
	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}
int display_jpeg(char *filename, fb_info fb_inf)
{
	fb_info jpeg_inf;
	
	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j,m,n;
    for(i = 0; i < 24; i++){
        for (j = 0; j < 32; j++){
            for(m = 0; m < 32; m=m+2){
                for(n = 0; n< 32; n=n+2){
                if(*status_p == 0) goto biao4;
                fb_pixel(fb_inf, j + 32*m, i + 24*n, buf32[j+32*m + (i+24*n) * fb_inf.w]);
                fb_pixel(fb_inf, j + 32*(m+1), i + 24*(n+1), buf32[j+32*(m+1) + (i+24*(n+1)) * fb_inf.w]);
                fb_pixel(fb_inf, j + 32*m, fb_inf.h/20 - i - 1 + 24*(n+1), buf32[j+32*m + (fb_inf.h/20 - i - 1 +24*(n+1)) * fb_inf.w]);
                fb_pixel(fb_inf, j + 32*(m+1), fb_inf.h/20 - i  + 24*n, buf32[j+32*(m+1) + (fb_inf.h/20 - i - 1 +24*n) * fb_inf.w]);
               }
            }
            //usleep(100);
        } 
    }
biao4:
	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}
int display_jpeg_1(char *filename, fb_info fb_inf)
{

    fb_info jpeg_inf;

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    int i, j,m,a;
    for (j = 0; j < fb_inf.w; j=j+8){
        for(m = j, a= 0; m > 0 ;a++, m=m-8){
            for(i = 0; i < fb_inf.h; i++){
                fb_pixel(fb_inf, fb_inf.w - m,  i , buf32[fb_inf.w - j +a+  i * fb_inf.w]);
                fb_pixel(fb_inf, fb_inf.w - m + 1,  i , buf32[fb_inf.w - j+a +  i * fb_inf.w]);
                fb_pixel(fb_inf, fb_inf.w - m + 2,  i , buf32[fb_inf.w - j+a +  i * fb_inf.w]);
                fb_pixel(fb_inf, fb_inf.w - m + 3,  i , buf32[fb_inf.w - j+a +  i * fb_inf.w]);
                fb_pixel(fb_inf, fb_inf.w - m + 4,  i , buf32[fb_inf.w - j+a +  i * fb_inf.w]);
                fb_pixel(fb_inf, fb_inf.w - m + 5,  i , buf32[fb_inf.w - j+a +  i * fb_inf.w]);
                fb_pixel(fb_inf, fb_inf.w - m + 6,  i , buf32[fb_inf.w - j+a +  i * fb_inf.w]);
                fb_pixel(fb_inf, fb_inf.w - m + 7,  i , buf32[fb_inf.w - j+a +  i * fb_inf.w]);
                if(*status_p == 0) goto dong04;
            }
        }
    }
    for (j = fb_inf.w; j >= 0; j= j - 8){
        for(m = j, a= 0; m >= 0 ;a++, m=m-8){
            for(i = 0; i < fb_inf.h; i++){
                if(fb_inf.w - m + 7 < fb_inf.w)
                {
                    fb_pixel(fb_inf, fb_inf.w - m,  i , buf32[fb_inf.w - j +a+  i * fb_inf.w]);
                    fb_pixel(fb_inf, fb_inf.w - m + 1,  i , buf32[fb_inf.w - j+a+1 +  i * fb_inf.w]);
                    fb_pixel(fb_inf, fb_inf.w - m + 2,  i , buf32[fb_inf.w - j+a+2 +  i * fb_inf.w]);
                    fb_pixel(fb_inf, fb_inf.w - m + 3,  i , buf32[fb_inf.w - j+a+3 +  i * fb_inf.w]);
                    fb_pixel(fb_inf, fb_inf.w - m + 4,  i , buf32[fb_inf.w - j+a+4 +  i * fb_inf.w]);
                    fb_pixel(fb_inf, fb_inf.w - m + 5,  i , buf32[fb_inf.w - j+a+5 +  i * fb_inf.w]);
                    fb_pixel(fb_inf, fb_inf.w - m + 6,  i , buf32[fb_inf.w - j+a+6 +  i * fb_inf.w]);
                    fb_pixel(fb_inf, fb_inf.w - m + 7,  i , buf32[fb_inf.w - j+a+7 +  i * fb_inf.w]);
                }
                if(*status_p == 0) goto dong04;
            }
        }
    }
   dong04: 
    free(buf24);
    free(scale_buf);
    free(buf32);

    return 0;
}
int display_jpegkaiji(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;
	
	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j,a;
    for(a = 0; a < fb_inf.w-1; a++){
        for (j = fb_inf.w - a ; j > fb_inf.w - 40 - a; j--){
            for(i = 0; i < fb_inf.h - 1; i++){
                if(fb_inf.w -40 -a > 0)
                    fb_pixel(fb_inf, j, i, buf32[fb_inf.w -j +i*fb_inf.w]);
                if(*status_p == 0) goto dong00;
                }
        }
	    for(i = 0; i < fb_inf.h-1; i++){
			fb_pixel(fb_inf, fb_inf.w - a, i, buf32[fb_inf.w - a  + i * fb_inf.w]);
        }
        
    }
    dong00:
	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}

int display_baiye1(char *filename, fb_info fb_inf)
{

	fb_info jpeg_inf;
	
	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

	int i, j;
    int m,m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12,m13,m14;
    m = 1*fb_inf.w/16; m1 = 2*fb_inf.w/16; m2 = 3*fb_inf.w/16; m3 = 4*fb_inf.w/16;
    m4 = 5*fb_inf.w/16; m5 = 6*fb_inf.w/16; m6 = 7*fb_inf.w/16;
    m7 = 8*fb_inf.w/16; m8 = 9*fb_inf.w/16; m9 = 10*fb_inf.w/16; m10 = 11*fb_inf.w/16;
    m11 = 12*fb_inf.w/16; m12 = 13*fb_inf.w/16; m13 = 14*fb_inf.w/16; m14 = 15*fb_inf.w/16;

	for (j = 0; j < fb_inf.w/16; ++j){
	    for(i = 0; i < fb_inf.h; ++i){
			fb_pixel(fb_inf, j, i , buf32[j + i * fb_inf.w]);
			fb_pixel(fb_inf, m , i , buf32[m + i * fb_inf.w]);
			fb_pixel(fb_inf, m1, i , buf32[m1 +i * fb_inf.w]);
			fb_pixel(fb_inf, m2, i , buf32[m2 + i * fb_inf.w]);
			fb_pixel(fb_inf, m3, i , buf32[m3 + i* fb_inf.w]);
			fb_pixel(fb_inf, m4, i , buf32[m4 + i * fb_inf.w]);
			fb_pixel(fb_inf, m5, i , buf32[m5 + i* fb_inf.w]);
			fb_pixel(fb_inf, m6, i , buf32[m6 + i * fb_inf.w]);
			fb_pixel(fb_inf, m7, i , buf32[m7 +  i* fb_inf.w]);
			fb_pixel(fb_inf, m8, i , buf32[m8 + i * fb_inf.w]);
			fb_pixel(fb_inf, m9, i , buf32[m9 + i * fb_inf.w]);
			fb_pixel(fb_inf, m10, i , buf32[m10 + i * fb_inf.w]);
			fb_pixel(fb_inf, m11, i , buf32[m11 + i * fb_inf.w]);
			fb_pixel(fb_inf, m12, i , buf32[m12 + i * fb_inf.w]);
			fb_pixel(fb_inf, m13, i , buf32[m13 + i * fb_inf.w]);
			fb_pixel(fb_inf, m14, i , buf32[m14 + i * fb_inf.w]);
            if(*status_p == 0) goto dong09;

		}
        m++;m1++;m2++;m3++;m4++;m5++;m6++;m7++;m8++;m9++;m10++;m11++;m12++;m13++;m14++;
	}
dong09:
	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}
//int display_jpeg1(char *filename, fb_info fb_inf)
//{
//
//fb_info jpeg_inf;
//	
//u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
//u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
//u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
//
//int i, j;
//
//for(i = y; i < y+z; ++i){
//for (j = 0; j < fb_inf.w; ++j){
//
//jfb_pixel(fb_inf, j, i, buf32[j + i * fb_inf.w]);
//}
//}
//
//free(buf24);
//free(scale_buf);
//free(buf32);
//	
//return 0;
//}
int display_scale(char *filename, fb_info fb_inf)
{
	int i, j,m,n,a,b;
    a = fb_inf.w/2,b = fb_inf.h/2;
    for(m = fb_inf.w,n = fb_inf.h;m >= 0 && n >= 0; n = n - 24,m = m - 32)
        //for(m = fb_inf.w,n = fb_inf.h;m >= 0 && n >= 0; n = n - 20,m = m - 32)
    {

        fb_info jpeg_inf;

        fb_info fb_inff;
        fb_inff.h = fb_inf.h - n;
        fb_inff.w = fb_inf.w - m;
        fb_inff.bpp = fb_inf.bpp;
        fb_inff.fbmem = fb_inf.fbmem;
        
        u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
        u8_t * scale_buf = scale24(buf24, fb_inff, jpeg_inf);
        u32_t *buf32 = rgb24to32(scale_buf, fb_inff);

        for(i = 0; i < fb_inff.h; ++i){
            for (j = 0; j < fb_inff.w; ++j){
                fb_pixel(fb_inf, j + a, i+ b, buf32[j + i * fb_inff.w]);
            }
        }
        free(buf24);
        free(scale_buf);
        free(buf32);
            a = a - 16;
            b = b - 12;

        }
	return 0;
}
int display_scale2(char *filename, fb_info fb_inf)
{
	int i, j,m;
    for(m = fb_inf.w ;m > 0 ; m = m - 20)
    {

        fb_info jpeg_inf;

        fb_info fb_inff;
        fb_inff.h = fb_inf.h;
        fb_inff.w = m;
        fb_inff.bpp = fb_inf.bpp;
        fb_inff.fbmem = fb_inf.fbmem;
        
        u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
        u8_t * scale_buf = scale24(buf24, fb_inff, jpeg_inf);
        u32_t *buf32 = rgb24to32(scale_buf, fb_inff);

        for(i = 0; i < fb_inff.h; ++i){
            for (j = 0; j < fb_inff.w; ++j){
                fb_pixel(fb_inf,(fb_inf.w - fb_inff.w)/2 + j , i, buf32[j + i * fb_inff.w]);
            }
            for(j = 0 ;j < (fb_inf.w - fb_inff.w)/2 ; j++)
            {
                fb_pixel(fb_inf, j , i, 0);
                fb_pixel(fb_inf, j +(fb_inf.w - fb_inff.w)/2 + fb_inff.w , i, 0);
            }
        }
        free(buf24);
        free(scale_buf);
        free(buf32);

    }
    for(m = 0 ;m <= fb_inf.w; m = m + 20)
    {

        fb_info jpeg_inf;

        fb_info fb_inff;
        fb_inff.h = fb_inf.h;
        fb_inff.w = m;
        fb_inff.bpp = fb_inf.bpp;
        fb_inff.fbmem = fb_inf.fbmem;
        
        u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
        u8_t * scale_buf = scale24(buf24, fb_inff, jpeg_inf);
        u32_t *buf32 = rgb24to32(scale_buf, fb_inff);

        for(i = 0; i < fb_inff.h; ++i){
            for (j = 0; j < fb_inff.w; ++j){
                fb_pixel(fb_inf, (fb_inf.w - fb_inff.w)/2 + j , i, buf32[j + i * fb_inff.w]);
            }
        }
        free(buf24);
        free(scale_buf);
        free(buf32);

        }
	return 0;
}
