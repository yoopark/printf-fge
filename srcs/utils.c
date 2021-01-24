/*
**	Yongjun Park
**	Created	2021. 1. 23.
**	utils.c
*/

#include "printf_fge_internal.h"

bool		_isdigit(char c)
{
	return ('0' <= c && c <= '9');
}

void		*_memset(void *p, char c, size_t n)
{
	for (size_t i = 0 ; i < n ; ++i)
		((unsigned char*)p)[i] = c;
	return p;
}

void		_bzero(void *p, size_t n)
{
	_memset(p, 0, n);
}

size_t		_strlen(const char *s)
{
	size_t		len = 0;
	
	while (s[len] != '\0')
		++len;
	return len;
}

void		_putchar(const char c)
{
	write(STDOUT_FILENO, &c, 1);
	++g_info.return_val;
}

void		_putstr(const char *s)
{
	write(STDOUT_FILENO, s, _strlen(s));
	g_info.return_val += _strlen(s);
}

void		*_calloc(size_t n, size_t per)
{
	void		*p;

	p = malloc(n * per);
	if (!p)
		return (NULL);
	_bzero(p, n * per);
	return p;
}

size_t		_strlen_to_charset(const char *s, const char *charset)
{
	size_t		len = 0;

	while (s[len] != '\0') {
		if (_strchr(charset, s[len]))
			return len;
		++len;
	}
	return len;
}

void		_putstr_with_len(const char *s, size_t len)
{
	write(STDOUT_FILENO, s, len);
	g_info.return_val += len;
}

char		*_strchr(const char *s, char c)
{
	for (size_t i = 0 ; s[i] != '\0' ; ++i) {
		if (s[i] == c)
			return (char*)(s + i);
	}
	if (c == '\0')
		return (char*)(s + _strlen(s));
	return NULL;
}

unsigned	MASK(int n)
{
	unsigned	mask = 0;

	for (int i = 0 ; i < n ; ++i)
		mask |= 0b1 << i;
	return mask;
}

void		*_memmove(void *dst, const void *src, size_t n)
{
	if (!n)
		return dst;
	if (src < dst) {
		for (size_t i = n - 1 ; i != (size_t)-1 ; --i)
			((unsigned char*)dst)[i] = ((const unsigned char*)src)[i];		
	} else {
		for (size_t i = 0 ; i < n ; ++i)
			((unsigned char*)dst)[i] = ((const unsigned char*)src)[i];		
	}
	return dst;
}

char		*_strncpy(char *dst, const char *src, size_t n)
{
	for (size_t i = 0 ; i < n ; ++i)
		dst[i] = src[i];
	dst[n] = '\0';
	return dst;
}

char		*_strcpy(char *dst, const char *src)
{
	return _strncpy(dst, src, _strlen(src));
}

char		*_strndup(const char *s, size_t n)
{
	char		*return_str;

	return_str = (char*)malloc(n + 1);
	if (!return_str)
		return NULL;
	return _strncpy(return_str, s, n);
}

char		*_strdup(const char *s)
{
	return _strndup(s, _strlen(s));
}

int			_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i = 0;

	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
		++i;
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}

int			_strcmp(const char *s1, const char *s2)
{
	return (_strncmp(s1, s2, _max_size(_strlen(s1), _strlen(s2))));
}

size_t		_max_size(size_t x, size_t y)
{
	return (x > y ? x : y);
}

size_t		_min_size(size_t x, size_t y)
{
	return (x < y ? x : y);
}

size_t		_max(int x, int y)
{
	return (x > y ? x : y);
}

size_t		_min(int x, int y)
{
	return (x < y ? x : y);
}

char		*_strjoin(const char *s1, const char *s2)
{
	char		*s;

	if (!s1 || !s2)
		return NULL;
	s = (char*)malloc(_strlen(s1) + _strlen(s2) + 1);
	if (!s)
		return NULL;
	s[_strlen(s1) + _strlen(s2)] = '\0';
	_strcpy(s, s1);
	_strcpy(s + _strlen(s1), s2);
	return s;
}

char		*_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char		*s;

	if (!s1 || !s2 || !s3)
		return NULL;
	s = (char*)malloc(_strlen(s1) + _strlen(s2) + _strlen(s3) + 1);
	if (!s)
		return NULL;
	s[_strlen(s1) + _strlen(s2) + _strlen(s3)] = '\0';
	_strcpy(s, s1);
	_strcpy(s + _strlen(s1), s2);
	_strcpy(s + _strlen(s1) + _strlen(s2), s3);
	return s;
}

static size_t	ptrSize(const char *s, char c)
{
	size_t		i = 0;
	size_t		return_val = 0;

	while (s[i] != '\0') {
		if (s[i] == c)
			++i;
		else {
			++return_val;
			while (s[i] != '\0' && s[i] != c)
				++i;
		}
	}
	return return_val;
}

char		**_split(const char *s, char c)
{
	char		**return_map;
	size_t		word_cnt = 0;

	if (!s)
		return NULL;
	return_map = (char**)_calloc(ptrSize(s, c) + 1, sizeof(char*));
	if (!return_map)
		return NULL;
	while (*s != '\0') {
		if (*s == c)
			++s;
		else {
			size_t i = 0;
			while (s[i] != '\0' && s[i] != c)
				++i;
			if (!(return_map[word_cnt] = _strndup(s, i))) {
				for (size_t i = 0 ; return_map[i] != NULL ; ++i)
					free(return_map[i]);
				free(return_map);
				return NULL;
			}
			++word_cnt;
			s += i;
		}
	}
	return return_map;
}

char		_to_nbr(char c)
{
	return (c - '0');
}

char		_to_digit(char c)
{
	return (c + '0');
}

char		*_ltrim(char *s, char c)
{
	char		*return_str;
	size_t		start = 0;

	while (s[start] == c)
		++start;
	return_str = _strdup(s + start);
	if (!return_str)
		return NULL;
	return return_str;
}