#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <pthread.h>

#include "common.h"

#define FB_DEVICE "/dev/fb0"
extern pthread_mutex_t mice_lock;

int init_fb(fb_info *fb_inf)
{
	int fd;

	if ((fd = open(FB_DEVICE, O_RDWR)) < 0){
		fprintf(stderr, "Open %s failed:%s\n", FB_DEVICE, strerror(errno));
		return -1;
	}

	struct fb_var_screeninfo fb_var;
	
	if (ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0){
		fprintf(stderr, "fb ioctl failed:%s\n", strerror(errno));
		return -1;
	}
	
	fb_inf->w = fb_var.xres;
	fb_inf->h = fb_var.yres;
	fb_inf->bpp = fb_var.bits_per_pixel;
#if 0
	printf("width:%d\thign:%d\tbpp:%d\n",
		  fb_inf->w, fb_inf->h, fb_inf->bpp);
#endif	
	fb_inf->fbmem = mmap(0, fb_inf->w * fb_inf->h * fb_inf->bpp /8,
					 PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (fb_inf->fbmem == MAP_FAILED){
		fprintf(stderr, "fb mmap failed:%s\n", strerror(errno));
		return -1;
	}
	
	close(fd);
	
	return 0;
}

int fb_pixel(fb_info fb_inf, int x, int y, u32_t color)
{
    
	u8_t *pos = (u8_t*)fb_inf.fbmem + (fb_inf.w * y + x) * fb_inf.bpp/8;

	switch (fb_inf.bpp){
	case 32:				  /* 32 bits */
		*(pos + 3) = color >> 24;
	case 24:				  /* 24 bits */
		*(pos + 2) = color >> 16;
	case 16:	  		       /* 16 bits */
		*(pos + 1) = color >> 8;
	case 8:			      /* 8 bits */
		*pos = color;
		return 0;
	default:
		return -1;
	}

	return -1;

}

/* painting horizontal */
int fb_pixel_row(fb_info fb_inf, int x, int y, int len, u32_t color)
{
	int i;
#if 1
	for(i = x; i < len; i++){
		fb_pixel(fb_inf,x+i, y, color);
	}
#else
	/* FIXME: not */
//	memset(fb_inf.fbmem + (y * fb_inf.w + x) * fb_inf.bpp/8, color, len * 
#endif

	return 0;
}

int fb_test(void)
{

	printf("Framebuffer Test\n");
	
	fb_info fb_inf;
	if(init_fb(&fb_inf) < 0)
		return -1;
	printf("Framebuffer  Test fb_pixel\n");
	
	/* point test */
//	point_t p, p2; p.x = 640;	p.y = 400;
	fb_pixel(fb_inf, 640, 400, 0xFFFFFFFF);

	/* line test*/
//	p.x = 0; p.y = 200;
//	p2.x = 1280, p2.y = 200;
	fb_pixel_row(fb_inf, 0, 200, 1280, 0xFF0000);
	

	munmap(fb_inf.fbmem, fb_inf.w * fb_inf.h * fb_inf.bpp / 8);
	return 0;
}

