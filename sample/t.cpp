//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <map>
#include <time.h>
#include <set>
#include <string>
#include <vector>
//INSERT INTO `tbl_operate_activity` VALUES ('26', '1404882000', '1404968400', '0', '100', '0', 'test', 'test', '2', '210');
void main(int argc, char* argv[])
{
	struct tm tmNow;
	time_t iNow=1405416233;	
	printf("%d\n",iNow);
	localtime_s(&tmNow,&iNow);
	printf("%d-%d-%d %d:%d:%d\n",tmNow.tm_year+1900,tmNow.tm_mon+1,tmNow.tm_mday,tmNow.tm_hour,tmNow.tm_min,tmNow.tm_sec);

	time_t iNext=mktime(&tmNow);
	printf("%d\n",iNext);

	tmNow. tm_sec=0;     /* seconds after the minute - [0,59] */
	tmNow. tm_min=0;     /* minutes after the hour - [0,59] */
	tmNow. tm_hour=8;    /* hours since midnight - [0,23] */
	tmNow. tm_mday=1;    /* day of the month - [1,31] */
	tmNow. tm_mon=0;     /* months since January - [0,11] */
	tmNow. tm_year=70;    /* years since 1900 */
      
	time_t iZero=mktime(&tmNow);
	printf("%d\n",iZero);

}
//KaAAABoAAAAqoAAAMwAAAC6gAAAKAAAAMKAAAAUAAAARpAAACgAAABKkAAAFAAAAFKQAAAIAAAAVpAAABQAAABekAAACAAAAGKQAAAoAAAD6pwAADAAAAA==