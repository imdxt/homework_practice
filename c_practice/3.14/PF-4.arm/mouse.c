#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include <unistd.h>

#include "common.h"

#define C_WIDTH  10
#define C_HEIGHT 17
#define T___     0X5a5a
#define BORD     0x0
#define X___     0xFFFFFFFF
unsigned long save_cursor[C_WIDTH * C_HEIGHT];

static unsigned long cursor_pixel[C_WIDTH * C_HEIGHT] = {
  BORD, T___, T___, T___, T___, T___, T___, T___, T___, T___,
  BORD, BORD, T___, T___, T___, T___, T___, T___, T___, T___,
  BORD, X___, BORD, T___, T___, T___, T___, T___, T___, T___,
  BORD, X___, X___, BORD, T___, T___, T___, T___, T___, T___,
  BORD, X___, X___, X___, BORD, T___, T___, T___, T___, T___,
  BORD, X___, X___, X___, X___, BORD, T___, T___, T___, T___,
  BORD, X___, X___, X___, X___, X___, BORD, T___, T___, T___,
  BORD, X___, X___, X___, X___, X___, X___, BORD, T___, T___,
  BORD, X___, X___, X___, X___, X___, X___, X___, BORD, T___,
  BORD, X___, X___, X___, X___, X___, X___, X___, X___, BORD,
  BORD, X___, X___, X___, X___, X___, BORD, BORD, BORD, BORD,
  BORD, X___, X___, BORD, X___, X___, BORD, T___, T___, T___,
  BORD, X___, BORD, T___, BORD, X___, X___, BORD, T___, T___,
  BORD, BORD, T___, T___, BORD, X___, X___, BORD, T___, T___,
  T___, T___, T___, T___, T___, BORD, X___, X___, BORD, T___,
  T___, T___, T___, T___, T___, BORD, X___, X___, BORD, T___,
  T___, T___, T___, T___, T___, T___, BORD, BORD, T___, T___
};

int mouse_open(char *device_name, int *fd)
{
	if (NULL == device_name)
		device_name = "/dev/input/mice";
	
	*fd = open(device_name, O_RDONLY | O_NONBLOCK);
	if(*fd < 0){
		fprintf(stderr, "Open %s:%s\n", device_name, strerror(errno));
		exit(1);
	}
	
	return 0;
}

int mouse_parse(const u8_t *buf, mouse_event_t* mevent)
{
	switch(buf[0] & 0x7){
	case 1:						/* left */
		mevent->button = 1;
		break;
	case 2:
		mevent->button = 2;		/* right */
		break;
	case 4:
		mevent->button = 3;		/* middle */
		break;
	default:
        mevent->button = 0;
		break;
	}
	mevent->x =  buf[1] - ((buf[0] & 0x10) ? 256 : 0);
	mevent->y = -buf[2] + ((buf[0] & 0x20) ? 256 : 0); 
	return 0;
}

/* cursor */

static int fb_pixel_m(fb_info fb_inf, int x, int y, u32_t color)
{
/* 16 bits */
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

int fb_restorecursor(fb_info fb_inf, int x, int y)
{
	int i, j;
	u32_t color;
	for (j = 0;j<C_HEIGHT;j++)
    {
		for (i = 0;i<C_WIDTH;i++)
        {
			color = save_cursor[i + j * C_WIDTH];
			fb_pixel_m(fb_inf,x+i,y+j,color);
		}
	}
	
	return 0;
}
int  fb_savecursor (fb_info fb_inf,int x,int y)
{
	int i,j;
	u32_t color;

	for (j = 0;j<C_HEIGHT;j++)
	{
		for (i = 0;i<C_WIDTH;i++)
		{
  			color = *(u32_t*)(fb_inf.fbmem + ((y + j) * fb_inf.w + x + i) * fb_inf.bpp/8);
			save_cursor[i + j * C_WIDTH] = color;
		}
	}
	return 0;
}

int  fb_drawcursor(fb_info fb_inf, int x, int y)
{
	int i,j;
	unsigned int color;

	fb_savecursor (fb_inf,x,y);

	for (j = 0;j<C_HEIGHT;j++)
	{
		for (i = 0;i<C_WIDTH;i++)
		{
			color = cursor_pixel[i + j * C_WIDTH];
			if (color != T___)
				fb_pixel_m(fb_inf,x+i,y+j,color);
		}
	}
	return 0;
}

