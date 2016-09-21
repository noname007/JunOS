/*
 *  string/strspn.c
 *
 *  This file is part of JunOS C Library.
 *  
 *  Copyright (C) 2016, Liu Xiaofeng <lxf.junos@aliyun.com>
 *  Licensed under MIT, http://opensource.org/licenses/MIT.
 */

#include <string.h>

size_t strspn(const char *s1, const char *s2)
{
	char *ts1, *ts2;

	for (ts1 = (char *) s1; *ts1; ts1++) {
		for (ts2 = (char*) s2; *ts2; ts2++) {
			if (*ts1 == *ts2)
				break;
		}
		if (*ts2 == '\0')
			break;

	}
	return (size_t) (ts1 - s1);
}
