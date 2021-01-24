/*
**	Yongjun Park
**	Created	2021. 1. 23.
**	fb2struct.c
*/

#include "printf_fge_internal.h"

SFloat		fb2struct(float_bits fb)
{
	SFloat		sf;

	sf.sign = (bool)(fb >> 31);
	sf.exponent = (fb >> 23) & MASK(8);
	sf.fraction = fb & MASK(23);
	return sf;
}

float_bits	struct2fb(SFloat sf)
{
	return (	((float_bits)sf.sign << 31) | 
				((sf.exponent & MASK(8)) << 23) | 
				(sf.fraction & MASK(23))
			);
}