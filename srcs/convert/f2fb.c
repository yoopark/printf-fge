/*
**	Yongjun Park
**	Created	2021. 1. 23.
**	f2fb.c
*/

#include "printf_fge_internal.h"

float_bits		f2fb(float f)
{
	return (*(float_bits*)&f);
}

float			fb2f(float_bits fb)
{
	return (*(float*)&fb);
}