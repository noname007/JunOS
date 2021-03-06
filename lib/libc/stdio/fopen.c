/*
 *  stdio/fopen.c
 *
 *  This file is part of JunOS C Library.
 *  
 *  Copyright (C) 2016, Liu Xiaofeng <lxf.junos@aliyun.com>
 *  Licensed under MIT, http://opensource.org/licenses/MIT.
 */

#include "stdio_loc.h"

FILE *fopen(const char *filename, const char *mode)
{
	int fd;
	FILE *f;

	fd = open(filename, O_RDWR | O_CREAT);
	if (fd < 0)
		return NULL;

	for (int i = 0; i < MAX_OPEN; i++) {
		if (__iotab[i]._flag)
			continue;
		f = &__iotab[i];
		f->_fd=fd;
		f->_flag=_IOFBF;
		f->_cnt=0;
		f->_bufsize=0;
		f->_buf=NULL;
		f->_ptr=NULL;
		return f;
	}
	return NULL;
}
