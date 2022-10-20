#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

char *read_file(char *filename)
{
    char    *s = 0;
    long    length;
    FILE    *f = fopen(filename, "rb");

    if (f)
    {
            fseek(f, 0, SEEK_END);
            length = ftell(f);
            fseek(f, 0, SEEK_SET);
            s = malloc(length + 1);
            if (s)
                    fread(s, 1, length, f);
            s[length] = 0;
            fclose (f);
    }
    return (s);
}
int test_number = 0;

void T(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    va_list ap2;
    va_copy(ap2, ap);
    char s1[4096];
    int b1 = vsprintf(s1, fmt, ap);
    open("out", O_WRONLY | O_TRUNC, 0);
	int b2 = ft_vprintf(fmt, ap2);
    close(3);
    char *s2 = read_file("out");
    if (strcmp(s1, s2) || b1 != b2)
    {
        printf("TEST %d: \033[1;31mFAILED\033[0m\nfmt=\"%s\"\ns1 = \"%s\", b1 = %d\ns2 = \"%s\", b2 = %d\n",
                test_number, fmt, s1, b1, s2, b2);
		assert(0);
    }
    else
        printf("TEST %d: OK\n", test_number);
	free(s2);
    va_end(ap);
    va_end(ap2);
	test_number++;
}

#define SP(...)

int main(void)
{ //todo: for whatever reason on linux print("%p", 0) is (nil)
	//flag '0' is undefined with 'sp'
	    //#define T(...) printf(__VA_ARGS__); printf("\n");ft_printf(__VA_ARGS__) ; ft_printf("\n");
	#if 0
    T(1, "");
    T(2, "hello world");
    T(3, "%d%d%d%d", 1337, 0, -42, INT_MIN);
    T(4, "z%ia%ib%ic%id", 1337, 0, -42, INT_MIN);
    T(5, "%d%u p%u%u", -1, 0, -1, 42);
    T(6, "f%x %x %xt", 0xabcdef, 0, -1);
    T(7, "f%X %X %Xt", 0xabcdef, 0, -1);
    T(8, "ff%pa%p%pa", 0, (void *)(-1), (void *)(0xabcdef));
    T(9, "%sa%sa%sfff", "testing...", 0, "");
    T(10, "%c %c %c", 0, -1, 'F');
    T(11, "%%a%%p%%%%%%");
    T(12, "t%s%d%Xd%pf%uaa%%%cbbb%i%s\n", 0, -11, 0xfa, (void *)42, UINT32_MAX, ' ', 1, "finish");
    // '+' ' ' '#'
    T(13, "%+dff%s%+i%++++d%+d", 1, "??", 0, -1, INT_MAX); // '+'
    T(14, "% d%%%     i%p%   +d%+  d%    i", 0, -1, (void *)1, 42, INT_MAX, INT_MIN, INT_MIN); // ' '
    T(15, "%#X%###x%%%+d%#x%##X%#x", 14, 0xabcdef, -1, 0, UINT32_MAX, 0);
    // min width
    T(16, "%5d%10s%       2d%###10x%12p%21s%3c%   ++++ + +42i", 0, "ttt", 3, 0xab, 0, 0, 'f', INT_MAX);
    T(17, "dd%1u%    3iffa%%%50sff%###12xa", 0, 22, "aa", 0xff);
    // '-'
    T(18, "%--5d%-10s%   -    2db%-#-##-10x%--12p%21s%-3c%   ++++ + +42i", 0, "ttt", 3, 0xab, 0, 0, 'f', INT_MAX);
    T(19, "dd%--1u%    -3iffa%%%--50sff%-###12xa", 0, 22, "aa", 0xff);
    // '.'
    T(20, "%.d%.u%#.X%%% +.5d%  +.4i%#.5X", 0, 0, 0, -21, 1, 0x5f5);
    T(21, "%10.5d%-10.6d", 42, 16);
    T(22, " %.2x %.4d", 10, 4);
    // '0'
    T(23, "%0+10d%05d%0x%%%5s%15p%000042ut%%t", 42, 0, 0, "hel", (void *)-1, -1);

    T(25, "%11p%011.4u%010.5d%%%0#12.5x", 1, 0, 52, 0xfa);
	T(26, "%10.5s", "hello"); // TODO: again printf in linux output different results
	T(27, "%#5.2x %-10.8d %-35p %-14.6s %5.s %15.5s", 0xa, 0, (void *)42, "0000hello world", "00", "0000");
	T(28, "%0-5d", 4);
	#endif
	//T("04.d", 3);
	//ft_printf("%%");
	T("%05c", 421);
	//return (0);
	char *s = malloc(2);
	s[0] = 'a';
	s[1] = 'b';
	T("%.2s", s);
	T("%c", -42);
	T("%.u", 0);
	T("%0-5d", 4);
	 T("%d", 100);
	T("%d", INT32_MIN);
	T("%d", INT32_MAX + 95);
	T("%d", 0);
	T("a%da", 100);
	T("a%da", INT32_MIN);
	T("a%da", 0);

	printf("--> \"%%u\" SIMPLE\n");
    T("%u", 100);
	T("%u", UINT32_MAX);
	T("%u", UINT32_MAX + 95);
	T("%u", 0);
	T("a%ua", 100);
	T("a%ua", UINT32_MAX);
	T("a%ua", 0);

	printf("--> \"%%x && %%X\" SIMPLE\n");
    T("%x", 100);
	T("%x", UINT32_MAX);
	T("%x", UINT32_MAX + 95);
	T("%x", 0);
	T("a%xa", 100);
	T("a%xa", UINT32_MAX);
	T("a%xa", 0);
	T("%X", 100);
	T("%X", UINT32_MAX);
	T("%X", UINT32_MAX + 95);
	T("%X", 0);
	T("a%Xa", 100);
	T("a%Xa", UINT32_MAX);
	T("a%Xa", 0);

	printf("--> \"%%p\" SIMPLE\n");
    T("%p", (void *)0x100);
	T("%p", (void *)UINT64_MAX);
	T("%p", (void *)0x0);
	T("a%pa", (void *)0x100);
	T("a%pa", (void *)UINT64_MAX);
	T("a%pa", (void *)0);

	printf("--> \"%%s\" SIMPLE\n");
    T("%s", "Hello");
	T("%s", "");
	T("%s", NULL);
	T("a%sa", "Hello");
	T("a%sa", "");
	T("a%sa", NULL);
	T("%s", "%15d");

	printf("--> \"%%c\" SIMPLE\n");
    T("%c", 97);
	T("a%ca", 97);
	// T("%c", 0);  // TODO
	// T("a%ca", 0);	// TODO

	/*
	*******************************************
	*******************************************
	*/

	printf("--> \"%%d\" MIN_WIDTH\n");
    T("%2d", 100);
	T("%3d", 100);
	T("a%3da", 100);
	T("%4d", 100);
	T("%2d", -100);
	T("%3d", -100);
	T("%4d", -100);
	T("%4d", 0);
	T("%1d", 0);
	T("a%1da", 0);

	printf("--> \"%%p\" MIN_WIDTH\n");
	T("%2p", (void *)100);
	T("%3p", (void *)100);
	T("%4p", (void *)100);
	T("a%4pa", (void *)100);
	T("%6p", (void *)100);
    T("%4p", (void *)0x0);
	T("%1p", (void *)0x0);
	T("a%1pa", (void *)0x0);

	printf("--> \"%%s\" MIN_WIDTH\n");
	SP("EXPECTED","--> \"%%s\" MIN_WIDTH\n");
	SP("TESTS","--> \"%%s\" MIN_WIDTH\n");
    T("%2s", "ABC");
	T("%3s", "ABC");
	T("%4s", "ABC");
	T("a%4sa", "ABC");
	T("%1s", NULL);
	T("a%1sa", NULL);
	T("%6s", NULL);
	T("%7s", NULL);
	T("%4s", "");
	T("%1s", "");
	T("a%1sa", "");

	/*
	*******************************************
	*******************************************
	*/
	printf("--> \"%%d\" MIN_WIDTH AND -\n");
	SP("EXPECTED","--> \"%%d\" MIN_WIDTH AND -\n");
	SP("TESTS","--> \"%%d\" MIN_WIDTH AND -\n");
    T("%-2d", 100);
	T("%-3d", 100);
	T("a%-3da", 100);
	T("%-4d", 100);
	T("%-2d", -100);
	T("%-3d", -100);
	T("%-4d", -100);
	T("%-4d", 0);
	T("%-1d", 0);
	T("a%-1da", 0);

	printf("--> \"%%p\" MIN_WIDTH AND -\n");
	SP("EXPECTED","--> \"%%p\" MIN_WIDTH AND -\n");
	SP("TESTS","--> \"%%p\" MIN_WIDTH AND -\n");
	T("%-2p", (void *)100);
	T("%-3p", (void *)100);
	T("%-4p", (void *)100);
	T("a%-4pa", (void *)100);
	T("%-6p", (void *)100);
    T("%-4p", (void *)0x0);
	T("%-1p", (void *)0x0);
	T("a%-1pa", (void *)0x0);

	printf("--> \"%%s\" MIN_WIDTH AND -\n");
	SP("EXPECTED","--> \"%%s\" MIN_WIDTH AND -\n");
	SP("TESTS","--> \"%%s\" MIN_WIDTH AND -\n");
    T("%-2s", "ABC");
	T("%-3s", "ABC");
	T("%-4s", "ABC");
	T("a%-4sa", "ABC");
	T("%-1s", NULL);
	T("a%-1sa", NULL);
	T("%-6s", NULL);
	T("%-7s", NULL);
	T("%-4s", "");
	T("%-1s", "");
	T("a%-1sa", "");

	/*
	*******************************************
	*******************************************
	*/
	printf("--> \"%%d\" MIN_WIDTH AND 0\n");
	SP("EXPECTED","--> \"%%d\" MIN_WIDTH AND 0\n");
	SP("TESTS","--> \"%%d\" MIN_WIDTH AND 0\n");
    T("%02d", 100);
	T("%03d", 100);
	T("a%03da", 100);
	T("%04d", 100);
	T("%02d", -100);
	T("%03d", -100);
	T("%05d", -100);
	T("%04d", 0);
	T("%01d", 0);
	T("a%01da", 0);

	/*
	*******************************************
	*******************************************
	*/
	printf("--> \"%%d\" MIN_WIDTH AND .\n");
	SP("EXPECTED","--> \"%%d\" MIN_WIDTH AND .\n");
	SP("TESTS","--> \"%%d\" MIN_WIDTH AND .\n");
    T("%2.3d", 100);
	T("%3.3d", 100);
	T("a%3.3da", 100);
	T("%4.3d", 100);
	T("%2.3d", -100);
	T("%3.3d", -100);
	T("%4.3d", -100);
	T("%4.3d", 0);
	T("%1.3d", 0);
	T("a%1.3da", 0);
	T("%2.0d", 100);
	T("%3.0d", 100);
	T("a%3.0da", 100);
	T("%4.0d", 100);
	T("%2.0d", -100);
	T("%3.0d", -100);
	T("%4.0d", -100);
	T("%4.0d", 0);
	T("%1.0d", 0);
	T("%4.d", 100);
	T("%2.d", -100);
	T("%3.d", -100);
	T("%4.d", -100);
	T("%4.d", 0);
	T("%1.d", 0);
	T("a%1.0da", 0);
	T("%2.7d", 100);
	T("%15.7d", 100);
	T("a%3.7da", 100);
	T("%4.7d", 100);
	T("%2.7d", -100);
	T("%3.7d", -100);
	T("%15.7d", -100);
	T("%4.7d", 0);
	T("%1.7d", 0);
	T("a%1.7da", 0);
	/*
	printf("--> \"%%p\" MIN_WIDTH AND .\n");
	SP("EXPECTED","--> \"%%p\" MIN_WIDTH AND .\n");
	SP("TESTS","--> \"%%p\" MIN_WIDTH AND .\n");
	T("%2.3p", (void *)100);
	T("%3.3p", (void *)100);
	T("%4.3p", (void *)100);
	T("a%4.3pa", (void *)100);
	T("%6.3p", (void *)100);
    T("%4.3p", (void *)0x0);
	T("%1.3p", (void *)0x0);
	T("a%1.3pa", (void *)0x0);*/

	printf("--> \"%%s\" MIN_WIDTH AND .\n");
	SP("EXPECTED","--> \"%%s\" MIN_WIDTH AND .\n");
	SP("TESTS","--> \"%%s\" MIN_WIDTH AND .\n");
    T("%2.3s", "ABC");
	T("%3.3s", "ABC");
	T("%4.3s", "ABC");
	T("a%4.3sa", "ABC");
	T("%1.3s", NULL);
	T("a%1.3sa", NULL);
	T("%6.3s", NULL);
	T("%7.3s", NULL);
	T("%4.3s", "");
	T("%1.3s", "");
	T("a%1.3sa", "");
	T("%2.2s", "ABC");
	T("%3.2s", "ABC");
	T("%4.2s", "ABC");
	T("a%4.2sa", "ABC");
	T("%1.2s", NULL);
	T("a%1.2sa", NULL);
	T("%6.2s", NULL);
	T("%7.2s", NULL);
	T("%4.2s", "");
	T("%1.2s", "");
	T("a%1.2sa", "");
	T("%2.10s", "ABC");
	T("%3.10s", "ABC");
	T("%4.10s", "ABC");
	T("a%4.10sa", "ABC");
	T("%1.10s", NULL);
	T("a%1.10sa", NULL);
	T("%6.10s", NULL);
	T("%7.10s", NULL);
	T("%4.10s", "");
	T("%1.10s", "");
	T("a%1.10sa", "");
	T("%2.s", "ABC");
	T("%3.s", "ABC");
	T("%4.s", "ABC");
	T("a%4.sa", "ABC");
	T("%1.s", NULL);
	T("a%1.sa", NULL);
	T("%6.s", NULL);
	T("%7.s", NULL);
	T("%4.s", "");
	T("%1.s", "");
	T("a%1.sa", "");

	/*
	*******************************************
	*******************************************
	*/
	printf("--> \"%%d\" ONLY .\n");
	SP("EXPECTED","--> \"%%d\" ONLY .\n");
	SP("TESTS","--> \"%%d\" ONLY .\n");
    T("%.3d", 100);
	T("%.3d", 100);
	T("a%.3da", 100);
	T("%.3d", 100);
	T("%.3d", -100);
	T("%.3d", -100);
	T("%.3d", -100);
	T("%.3d", 0);
	T("%.3d", 0);
	T("a%.3da", 0);
	T("%.0d", 100);
	T("%.0d", 100);
	T("a%.0da", 100);
	T("%.0d", 100);
	T("%.0d", -100);
	T("%.0d", -100);
	T("%.0d", -100);
	T("%.0d", 0);
	T("%.0d", 0);
	T("%.d", 100);
	T("%.d", -100);
	T("%.d", -100);
	T("%.d", -100);
	T("%.d", 0);
	T("%.d", 0);
	T("a%.0da", 0);
	T("%.7d", 100);
	T("%5.7d", 100);
	T("a%.7da", 100);
	T("%.7d", 100);
	T("%.7d", -100);
	T("%.7d", -100);
	T("%5.7d", -100);
	T("%.7d", 0);
	T("%.7d", 0);
	T("a%.7da", 0);
}