// LoadDataFromFile.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <stdio.h>
#include <tchar.h>

#include <time.h>

int _tmain(int argc, _TCHAR* argv[])
{

	time_t tt = time(NULL);
	tm t;
	localtime_s(&t, &tt);
	printf("current year is %d;current month is %d;current date of month is %d\r\n",
		1900 + t.tm_year,
		1 + t.tm_mon/*��month�ķ�ΧΪ0-11*/,
		t.tm_mday);

	printf("\t����ʱ�䣺%d-%d-%d %d:%d:%d\r\n",
		t.tm_year + 1900,
		t.tm_mon + 1,
		t.tm_mday,
		t.tm_hour,
		t.tm_min,
		t.tm_sec);

	time_t t2 = mktime(&t);
	//ctime();
	return 0;
}

