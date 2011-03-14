/*
 *  link.c
 *  by Tony
 *  2010.2.24
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <dirent.h>

typedef struct node jpeg_file_t;

struct node 
{
	char *filename;
	char *info;
	jpeg_file_t *next;
};

jpeg_file_t * NODE(const char *filename, const char *info,
				   jpeg_file_t *next)
{
	jpeg_file_t *tmp;
	tmp = (jpeg_file_t *)malloc(sizeof(*tmp)
								+ strlen(filename) + 1
								+ strlen(info) + 1);

	tmp->filename = (char *)tmp + sizeof(*tmp);
	strcpy(tmp->filename, filename);

	tmp->info = tmp->filename + strlen(filename) + 1;
	strcpy(tmp->info, info);

	tmp->next = next;

	return tmp;
}



int init_link(const char *pathname)
{

	DIR *dp;
	if((dp = opendir(pathname)) == NULL)
		return -1;
	struct dirent *sdir;

	while((sdir = readdir(dp)) != NULL)
		if(sdir->d_type == DT_REG)
			printf("%s\t:%d\n", sdir->d_name, sdir->d_type);

	closedir(dp);
	return 0;
}

	
