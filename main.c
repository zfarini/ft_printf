#include  "ft_printf.h"
#include <stdint.h>
#include <limits.h>

int main()
{
	#define T(fmt, ...) printf(fmt"\n", __VA_ARGS__), fflush(stdout), ft_printf(fmt"\n", __VA_ARGS__)
	//T(" %% ", 5);
	T(" %04d ", -14);
	T(" %#x ", 0);
	T(" %.2x ", -1);
	T(" %.2i ", -1);
	//T(" %-9p %-10p ", LONG_MIN, LONG_MAX);
	//T("%-1c%-2ct", '0', 'c');
	//T("%---+++ 00 30.20dt", 42);
	//T("%+10.0dt", 0);
	//T("%010.5d", 42);
}