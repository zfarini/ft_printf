#include  "ft_printf.h"

int main()
{
	#define T(fmt, ...) printf(fmt"\n", __VA_ARGS__), fflush(stdout), ft_printf(fmt"\n", __VA_ARGS__)
	T(" %% ", 5);
	//T("%---+++ 00 30.20dt", 42);
	//T("%+10.0dt", 0);
	//T("%010.5d", 42);
}