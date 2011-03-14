#include <string.h>
#include <errno.h>

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

int create_jpeg(const char *filejpeg, const char *newfile, fb_info fb_inf)
{
	fb_info jpeg_inf;
	
	u8_t *buf24 = decode_jpeg(filejpeg, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

//	FILE *fp = fopen("file.jpg", "w+");
	FILE *fp = fopen(newfile, "w+");
	if (fp == NULL){
		fprintf(stderr, "fopen %s:%s\n",
			   newfile, strerror(errno));
		return -1;
	}
	
	int i, j;
	for(i = 0; i < fb_inf.h; ++i){
		for (j = 0; j < fb_inf.w; ++j){
			fwrite(&buf32[j + i * fb_inf.w], 4, 1,fp);
		}
	}

	free(buf24);
	free(scale_buf);
	free(buf32);
	fclose(fp);
	return 0;
}

int basic_disp(const char * filename, fb_info fb_inf)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL){
		fprintf(stderr, "fopen %s:%s\n",
			   filename, strerror(errno));
		return -1;
	}
	int i, j;
	
	for(i = 0; i < fb_inf.h; ++i){
		for (j = 0; j < fb_inf.w; ++j){
			int a;
			if (fread(&a, 4, 1, fp) != 0)
				fb_pixel(fb_inf, j, i, a);
		}
	}
	
	fclose(fp);
	
	return 0;
}

