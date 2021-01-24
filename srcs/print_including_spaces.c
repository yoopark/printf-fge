/*
**	Yongjun Park
**	Created	2021. 1. 23.
**	print_including_spaces.c
*/

#include "printf_fge_internal.h"

static size_t	getWholeStrLen(char *sign, const char *s, SConversion *conversion_info)
{
	size_t		return_val = 0;

	if (conversion_info->sign_flag && _strcmp(sign, "+") == 0)
		++return_val;
	return_val += _strlen(s);
	return (_max_size(return_val, (size_t)conversion_info->width));
}

static void		rightAlignStr(char *s)
{
	size_t		save_pos = _strlen(s) - 1;

	for (size_t i = _strlen(s) - 1 ; i != (size_t)-1 ; --i)
	{
		if (s[i] != '#') {
			_memmove(s + save_pos, s + i, 1);
 			if (i != save_pos)
	 			s[i] = '#';
			--save_pos;
		}
	}
}

static void		insertStr(char *s, char *new_s)
{
	if (s[0] != '#') // 일반화 가능한 조건은 아님.
		_memmove(s + _strlen(new_s), s, _strlen_to_charset(s, "#"));
	_memmove(s, new_s, _strlen(new_s));
}

static void		replaceStr(char *s, char from, char to)
{
	for (size_t i = 0 ; s[i] != '\0' ; ++i) {
		if (s[i] == from)
			s[i] = to;
	}
}

void			printIncludingSpaces(char *sign, const char *s, SConversion *conversion_info)
{
	char		*whole_str;
	size_t		whole_str_len = getWholeStrLen(sign, s, conversion_info);

	if (!(whole_str = (char*)malloc(whole_str_len + 1)))
		g_info.is_error = true;
	_memset(whole_str, '#', whole_str_len);
	whole_str[whole_str_len] = '\0';
	
	_memmove(whole_str, s, _strlen(s));
	if (conversion_info->alignment_flag != '-')
		rightAlignStr(whole_str);
	
	// Insert sign string
	if (conversion_info->sign_flag || _strcmp(sign, "-") == 0) {
		if (conversion_info->sign_flag == ' ')
			insertStr(whole_str, " ");
		else
			insertStr(whole_str, sign);
		if (conversion_info->alignment_flag != '0' && conversion_info->alignment_flag != '-')
			rightAlignStr(whole_str);
	}
	if (conversion_info->alignment_flag == '0')
		replaceStr(whole_str, '#', '0');
	else
		replaceStr(whole_str, '#', ' ');
	_putstr(whole_str);
	free(whole_str);
}