#include "src/ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>


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

void T(int test_number, char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    va_list ap2;
    va_copy(ap2, ap);
    char s1[8192];
    int b1 = vsprintf(s1, fmt, ap);
	int stdout_copy = dup(1);
	close(1);

    assert(open("out", O_WRONLY | O_TRUNC | O_CREAT, 0644) == 1);
	int b2 = ft_vprintf(fmt, ap2);
	close(1);
	dup2(stdout_copy, 1);
	close(stdout_copy);
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
}

int main(void)
{ 
    T(1, "");
    T(2, "hello world");
	T(3, "t%%t %%%%");
    T(3, "%d%d%d%d", 1337, 0, -42, INT_MIN);
    T(4, "z%ia%ib%ic%id", 1337, 0, -42, INT_MIN);
    T(5, "%d%u p%u%u", -1, 0, -1, 42);
    T(6, "f%x %x %xt", 0xabcdef, 0, -1);
    T(7, "f%X %X %Xt", 0xabcdef, 0, -1);
    T(8, "ff%pa%p%pa", 0, (void *)(-1), (void *)(0xabcdef));
    T(9, "%sa%sa%sfff", "testing...", 0, "");
    T(10, "%c %c %c%c%c%c", 0, -1, 'F', INT_MIN, -42, '\n');
    T(11, "%%a%%p%%%%%%");
    T(12, "t%s%d%Xd%pf%uaa%%%cbbb%i%s\n", 0, -11, 0xfa, (void *)42, UINT32_MAX, ' ', 1, "finish");
    // '+' ' ' '#'
    T(13, "%+dff%s%+i%++++d%+d", 1, "??", 0, -1, INT_MAX); // '+'
    T(14, "% d%%%     i%p%   +d%+  d%    i", 0, -1, (void *)1, 42, INT_MAX, INT_MIN, INT_MIN); // ' '
    T(15, "%#X%###x%%%+d%#x%##X%#x", 14, 0xabcdef, -1, 0, UINT32_MAX, 0);
    // min width
    T(16, "%5d%10s%       2d%###10x%12p%21s%3c%   ++++ + +42i", 0, "ttt", 3, 0xab, 0, "v", 'f', INT_MAX);
	//return (0);
    T(17, "dd%1u%    3iffa%%%50sff%###12xa", 0, 22, "aa", 0xff);
    // '-'
	T(18, "%--5d%-10s%   -    2db%-#-##-10x%--12p%21s%-3c%   ++++ + +42i", 0, "ttt", 3, 0xab, 0, "aba", 'f', INT_MAX);
	T(19, "dd%--1u%    -3iffa%%%--50sff%-###12xa", 0, 22, "aa", 0xff);
	// '.'
	T(20, "%.d%.u%#.X%%% +.5d%  +.4i%#.5X", 0, 0, 0, -21, 1, 0x5f5);
	T(21, "%10.5d%-10.6d", 42, 16);
	T(22, " %.2x %.4d", 10, 4);
	// '0'
	T(23, "%0+10d%05d%0x%%%5s%15p%000042ut%%t%04.d", 42, 0, 0, "hel", (void *)-1, -1, 3);

	T(25, "%11p%011.4u%010.5d%%%0#12.5x", 1, 0, 52, 0xfa);
	T(26, "%10.5s", "hello"); // TODO: again printf in linux output different results
	T(27, "%#5.2x %-10.8d %-35p %-14.6s %5.s %15.5s", 0xa, 0, (void *)42, "0000hello world", "00", "0000");
	T(28, "%0-5d", 4);

	char *s = malloc(2);
	s[0] = s[1] = 'a';
	T(29, "%.2s%.3s%-10.3s%.s%-2.2s", s, "", "abcde", "", "abc");
	free(s);

	T(30, "%.000d%.u%#.00x%.0X%.00i", 0, 0, 0, 0, 0);
	T(31, "%    +++ d% i%   i", 0, -128, 42);
	T(32, "%#5.0x%#1.X%#15.3X%%%#.1x", 0, 0, -1, 0xff);
	T(33, "v%0  +15d%0#3x%   +++ 0000 + 1337i%0010u%0utt%%", 42, 0xd, 69, 0, -1);
	T(34, "%000-d%-4ut%00  ++-14i", 4, 0, INT_MAX);
	T(35, "%2s%3s%4saba%4sabba%1s%42s%1s", "frt", "frt", "frt", "frt", "", "", "");
	T(37, "%1s%42s%1s", 0, 0, "");
	T(38, "%.3d%.4d%#.4x%#.4X%.3d%.4d%.2i%++ .d%5.7d", 100, 100, 0xfff, 0xabcd, -100, -1000, -100, 0, 100);
	T(39, "%5.7d%5.7u%%aba%16.x%+ 11.5i", -100, 4, 0xc, 44);
	T(40, "%10p%1pt%-14p", (void *)0, (void *)12, (void *)0xfaf);
}