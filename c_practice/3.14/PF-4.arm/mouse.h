/*
 *  2010.4.5
 *  mouse.h
 */

#ifndef __MOUSE_H__
#define __mOUSE_H__

typedef struct 
{
	int x;
	int y;
	int button;
}mouse_event_t;
		
extern int mouse_open(char *device_name, int *fd);
extern int mouse_parse(const u8_t *buf, mouse_event_t* mevent);

extern int fb_restorecursor(fb_info fb_inf, int x, int y);
extern int fb_drawcursor(fb_info fb_inf, int x, int y);

extern int test_mouse(fb_info fb_inf);

#endif

