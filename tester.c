#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

int g_test_counter = 0;

#define T(fmt, ...) \
	{ \
		freopen("out1", "w", stdout);\
		FILE *f1 = fopen("out1", "wr"); \
		FILE *f2 = fopen("out2", "wr"); \
		int v1 = ft_printf(fmt, __VA_ARGS__); \
		int v2 = fprintf(f2, fmt, __VA_ARGS__); \
		char b1[4096], b2[4096]; \
		int failed = 0;\
		while (!failed) \
		{\
			char *s1 = fgets(b1, sizeof(b1), f1);\
			char *s2 = fgets(b2, sizeof(b2), f2);\
			if (!s1 || !s2)\
			{\
				if (s1 != s2)\
					failed = 1;\
				break;\
			}\
			else if (strcmp(s1, s2))\
				failed = 1;\
		}\
		if (failed || v1 != v2)\
		{\
			fprintf(f3, "FAILED TEST %d %d %d\n", g_test_counter, v1, v2); \
			exit(1);\
		}\
		else\
			fprintf(f3, "PASSED TEST %d\n", g_test_counter); \
		g_test_counter++;\
		fclose(f1), fclose(f2); \
	}

int main(int argc, char **argv)
{
	FILE *f3 = fopen("out3", "wr");
	T("%p%p", (void*)SIZE_MAX, (void*)0);
	T("%u%u", UINT32_MAX, 0);
	T("%d%d%i%i%d%i%d", INT_MIN, INT_MAX, INT_MIN, INT_MAX, 0, 0, -42);
	T("%x%x%X%X%%", 0, UINT32_MAX, 0, UINT32_MAX);
	T("%c%c%s%s", '\n', 0, (char *)0, "hi");
	T("%10d%5p%15x%5s%10s%4s%10c%%%0u%10X", 0, (void *)-1, 0xFF, (char *)0, "", "ff", 0, 0, UINT32_MAX);
	T("%+d%+i%+d", 0, -1, INT_MAX);
	T("% d% i% d", 0, -1, INT_MAX);
	T("%+ d%++++  4i", 0, 42);
	T("%#x%#X", 0, 0);
	T("%#10x%#5X", UINT32_MAX, 0x1337);
	T("%010d%0d%0 42i%0+13d%0+20d", 0, 42, 13, -1, INT_MAX);
	T("%.s%.2s%10.3s%%%.000s%-5.7st", (char *)0, (char *)0, "fffff", "pah", "ab");
	
	//T(" %-9p %-10p ", LONG_MIN, LONG_MAX);
	//T("%-1c%-2ct", '0', 'c');
	//T("%---+++ 00 30.20dt", 42);
	//T("%+10.0dt", 0);
	//T("%010.5d", 42);
}