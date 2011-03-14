#ifndef __COMMON_H__
#define __COMMON_H__

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

typedef unsigned char u8_t;
typedef struct 
{
	int w;				  /* width */
	int h;				  /* high */
	int bpp;				  /* bits per pixel */
	u8_t *fbmem;
}fb_info;

extern int decode(unsigned char const *, unsigned long);
extern void set_dsp(void);
extern int play(int *p);
extern int writedsp(int c);
typedef unsigned short u16_t;
typedef unsigned int u32_t;

extern char *mp3_name[3];
extern int display_song(int *p);
extern int disappear(fb_info fb_inf, int x, int y);
extern int restoresong(fb_info fb_inf, int x, int y);

typedef struct 
{
	int x;
	int y;
	int button;
}mouse_event_t;



/* ******************** mouse.c ******************** */
extern int mouse_open(char *device_name, int *fd);
extern int mouse_parse(const u8_t *buf, mouse_event_t* mevent);

extern int fb_restorecursor(fb_info fb_inf, int x, int y);
extern int fb_drawcursor(fb_info fb_inf, int x, int y);
extern int test_mouse(fb_info fb_inf);


/* ******************** fb.c ******************** */

/* initial framebuf */
extern int init_fb(fb_info *fb_inf);

/* drawing pixel */
extern int fb_pixel(fb_info fb_inf, int x, int y, u32_t color);

/* Framebuffer Test */
int fb_test(void);


/* ******************** jpeg.c ******************** */

/*This returns an array for a 24 bit image.*/
extern u8_t *decode_jpeg (const char *filename, fb_info *jpeg_inf);
extern int display_jpeg_dj(char *filename, fb_info fb_in);

extern u32_t * rgb24to32(u8_t *buf24, fb_info jpeg_inf);
extern u16_t * rgb24to16(u8_t *buf24, fb_info jpeg_inf);

extern u8_t * scale24(u8_t *buf24, fb_info new_inf, fb_info jpeg_inf);
extern int disp_four_pic(int start_num);


/* ******************** disp_jpeg.c ******************** */
/* display jpeg */
/*extern int display_one_small_jpeg(char *filename, fb_info fb_in, int x, int y);*/
extern int display_mid_jpeg(char *filename, fb_info fb_in, int x, int y);
extern int display_one_small_jpeg(u16_t *buf32, fb_info fb_in, int x, int y);
extern u16_t * decode_small_jpeg(char *filename, fb_info fb_in);


/* ******************** dong  display_jpeg.c ******************** */
extern int display_flash1(const char *filename, fb_info fb_inf);
extern int display_flash2(const char *filename, fb_info fb_inf);
extern int display_midtoside(const char *filename, fb_info fb_inf);
extern int display_xie1(const char *filename, fb_info fb_inf);
extern int display_four(const char *filename, fb_info fb_inf);
                
extern int fb_line1(const char *filename, fb_info fb_inf);
extern int fb_line2(const char *filename, fb_info fb_inf);
extern int fb_line3(const char *filename, fb_info fb_inf);
extern int fb_line4(const char *filename, fb_info fb_inf);
extern int display_scale1(char *filename, fb_info fb_inf,int jpeg_w,int jpeg_h);

extern int display_jpegkaiji(char *filename, fb_info fb_inf);
extern int display_jpeg111(char *filename, fb_info fb_inf);
extern int display_jpeg(char *filename, fb_info fb_inf);
extern int display_jpeg_1(char *filename, fb_info fb_inf);
extern int display_jpeg12(char *filename, fb_info fb_inf);
extern int display_jpeg13(char *filename, fb_info fb_inf);
extern int display_jpeg14(char *filename, fb_info fb_inf);
extern int display_jpeg1(char *filename, fb_info fb_inf,int y,int z);
extern int display_jpeg2(char *filename, fb_info fb_inf);
extern int display_scale(char *filename, fb_info fb_inf);
extern int display_scale2(char *filename, fb_info fb_inf);
// display_jpg3.c
extern int display_box(const char *filename, fb_info fb_inf, fb_info fb_xin);
extern int display_v_up(const char *filename, fb_info fb_inf, fb_info fb_xin);
extern int display_zig(const char *filename, fb_info fb_inf, fb_info fb_xin);
/*extern int display_scale(char *filename, fb_info fb_inf,int jpeg_w,int jpeg_h,int jpeg_x,int jpeg_y);*/
extern int display_baiye1(char *filename, fb_info fb_inf);

/* display jpeg */
/*extern int display_flash1(const char *filename, fb_info fb_inf, fb_info fb_xin, int x1, int x2);*/
/*extern int display_flash2(const char *filename, fb_info fb_inf, fb_info fb_xin, int x1, int x2);*/
/*extern int display_midtoside(const char *filename, fb_info fb_inf, fb_info fb_xin, int x, int y);*/
/*extern int display_xie1(const char *filename, fb_info fb_inf);*/
/*extern int display_four(const char *filename, fb_info fb_inf);*/
/* */
/*extern int fb_line1(const char *filename, fb_info fb_inf);*/
/*extern int fb_line2(const char *filename, fb_info fb_inf);*/
/*extern int fb_line3(const char *filename, fb_info fb_inf);*/
/*extern int display_scale1(char *filename, fb_info fb_inf,int jpeg_w,int jpeg_h);*/
/**/
/*extern int display_jpegkaiji(char *filename, fb_info fb_inf);*/
/*extern int display_jpeg111(char *filename, fb_info fb_inf);*/
/*extern int display_jpeg(char *filename, fb_info fb_inf);*/
/*extern int display_jpeg12(char *filename, fb_info fb_inf);*/
/*extern int display_jpeg13(char *filename, fb_info fb_inf);*/
/*extern int display_jpeg14(char *filename, fb_info fb_inf);*/
/*extern int display_jpeg1(char *filename, fb_info fb_inf,int y,int z);*/
/*extern int display_jpeg2(char *filename, fb_info fb_inf);*/
/*extern int display_scale(char *filename, fb_info fb_inf);*/
/*extern int display_scale2(char *filename, fb_info fb_inf);*/
/*// display_jpg3.c*/
/*extern int display_box(const char *filename, fb_info fb_inf, fb_info fb_xin);*/
/*extern int display_v_up(const char *filename, fb_info fb_inf, fb_info fb_xin);*/
/*extern int display_zig(const char *filename, fb_info fb_inf, fb_info fb_xin);*/
/**//**//**//**//**//**//**//*extern int display_scale(char *filename, fb_info fb_inf,int jpeg_w,int jpeg_h,int jpeg_x,int jpeg_y);*/
/*extern int display_baiye1(char *filename, fb_info fb_inf,int jpeg_w,int jpeg_h,int x1,int x2);*/


/* ******************** font.c ******************** */
extern int init_ft (const char *file, int size);
extern int display_string (const char *buf, int x, int y, fb_info fb_inf,u32_t color);


/* ******************** mouse.c ******************** */
extern int  fb_savecursor (fb_info fb_inf,int x,int y);
extern int fb_restorecursor(fb_info fb_inf, int x, int y);
extern int  fb_drawcursor(fb_info fb_inf, int x, int y);

/* ******************** disp-basic.c ******************** */
/* create jpeg middle data file */
extern int create_jpeg(const char *filejpeg, const char *newfile, fb_info fb_inf);
/* use middle data file to display */
extern int basic_disp(const char * filename, fb_info fb_inf);


/*********************change_color.c************************************/
extern int chang_color(int, int, u32_t);
#endif
