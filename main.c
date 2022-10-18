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

void T(int test_number, char *fmt, ...)
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
        printf("TEST %d: \033[1;31mFAILED\033[0m\ns1 = \"%s\", b1 = %d\ns2 = \"%s\", b2 = %d\n", 
                test_number, s1, b1, s2, b2);
    }
    else 
        printf("TEST %d: OK\n", test_number);
	free(s2);
    va_end(ap);
    va_end(ap2);
}

int main(void)
{

    //#define T(...) printf(__VA_ARGS__); printf("\n");ft_printf(__VA_ARGS__) ; ft_printf("\n"); 
    ;
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
    T(23, "%0+10d%05d%0x%%%05s%015p%  000042ut%%t", 42, 0, 0, "hel", (void *)-1, -1);
    T(69, "%010.5s", "hello", 'f');
    T(25, "%011.4p%011.4u%010.5d%%%0#12.5x", 1, 0, 52, 0xfa);
    //mix
   // T(26, );
}