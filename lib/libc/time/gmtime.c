/*
 *  time/gmtime.c
 *
 *  This file is part of JunOS C Library.
 *  
 *  Copyright (C) 2016, Liu Xiaofeng <lxf.junos@aliyun.com>
 *  Licensed under MIT, http://opensource.org/licenses/MIT.
 */

#include <time.h>

static int days_per_mth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static struct tm st;

struct tm *gmtime(time_t *t)
{
	struct tm *stm=&st;
	time_t time = *t;

	int year, mday, i;

	if (time < 0) /* negative times are bad */
		return 0;
	stm->tm_wday = ((time / DAY) + 4) % 7;

	year = 1970;
	for (;;) {
		if (time < YEAR)
			break;
		if ((year % 4) == 0) {
			if (time < LEAPYEAR)
				break;
			else
				time -= LEAPYEAR;
		} else
			time -= YEAR;
		year++;
	}
	stm->tm_year = year;
	mday = stm->tm_yday = time / DAY;
	days_per_mth[1] = (year % 4) ? 28 : 29;
	for (i = 0; mday >= days_per_mth[i]; i++)
		mday -= days_per_mth[i];
	stm->tm_mon = i;
	stm->tm_mday = mday + 1;
	time = time % DAY;
	stm->tm_hour = time / HOUR;
	time = time % HOUR;
	stm->tm_min = time / MIN;
	stm->tm_sec = time % MIN;
	stm->tm_isdst = 0;
	return stm;
}
