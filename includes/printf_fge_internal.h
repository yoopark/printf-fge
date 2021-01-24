/*
**	Yongjun Park
**	Created	2021. 1. 23.
**	printf_fge_internal.h
*/

#ifndef PRINTF_FGE_INTERNAL_H
# define PRINTF_FGE_INTERNAL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdbool.h>

# include <stdio.h>				// for testing

# define BIAS		0x7F		// 2^8 - 1

typedef unsigned	float_bits;

/*
** Naming printf() format
**
** ex) printf("%+10.2f Points\n", 0.1234);
**		%+-10.2f Points\n	=> format
**		%+-10.2f			=> conversion_str
** 	 	+					=> sign_flag
**		-					=> alignment_flag
**		10					=> width
** 		2					=> precision
**		f					=> specifier
*/

typedef struct		_SConversion
{
	char			sign_flag;
	char			alignment_flag;
	// bool			have_width;
	bool			have_precision;
	int				width;
	int				precision;
	char			specifier;
}					SConversion;

typedef struct		_SFloat
{
	bool			sign;
	unsigned		exponent;
	unsigned		fraction;
}					SFloat;

typedef struct		_SGlobal
{
	int				return_val;
	bool			is_error;
	va_list			arg_ptr;
}					SGlobal;

extern SGlobal		g_info;

bool		_isdigit(char c);
void		*_memset(void *p, char c, size_t n);
void		_bzero(void *p, size_t n);
size_t		_strlen(const char *s);
void		_putchar(const char c);
void		_putstr(const char *s);
void		*_calloc(size_t n, size_t per);
size_t		_strlen_to_charset(const char *s, const char *charset);
void		_putstr_with_len(const char *s, size_t len);
char		*_strchr(const char *s, char c);
unsigned	MASK(int n);
char		*_strncpy(char *dst, const char *src, size_t n);
char		*_strcpy(char *dst, const char *src);
char		*_strndup(const char *s, size_t n);
char		*_strdup(const char *s);
void		*_memmove(void *dst, const void *src, size_t n);
int			_strncmp(const char *s1, const char *s2, size_t n);
int			_strcmp(const char *s1, const char *s2);
size_t		_max_size(size_t x, size_t y);
size_t		_min_size(size_t x, size_t y);
size_t		_max(int x, int y);
size_t		_min(int x, int y);
char		*_strjoin(const char *s1, const char *s2);
char		*_strjoin3(const char *s1, const char *s2, const char *s3);
char		**_split(const char *s, char c);
char		_to_nbr(char c);
char		_to_digit(char c);
char		*_ltrim(char *s, char c);

float_bits	f2fb(float f);
float		fb2f(float_bits fb);
float_bits	struct2fb(SFloat sf);
SFloat		fb2struct(float_bits fb);
char		*struct2decimal(SFloat *sf);
char		*decimal2e(SConversion *conversion_info, char *decimal);
char		*decimal2f(SConversion *conversion_info, char *decimal);

void		setConversionInfo(SConversion *conversion_info, const char *s, size_t len);
void		printSpecifierF(SConversion *conversion_info, char *decimal);
void		printSpecifierG(SConversion *conversion_info, char *decimal);
void		printSpecifierE(SConversion *conversion_info, char *decimal);
void		printIncludingSpaces(char *sign, const char *s, SConversion *conversion_info);

char		*multiplyHalf(char *s); // 이후 수정
char		*add(char *s1, char *s2); // 이후 수정

#endif