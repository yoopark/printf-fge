/* fractiton2decimal */

static bool		getBitFromUnsigned(unsigned u, unsigned n);

/*
** 1.0	-> 0.5	-> 0.25	-> 0.125 -> 0.0625
** 1	-> 5	-> 25	-> 125	 -> 625
** By multiplying by 5, the effect can be equal to 1/2 the fraction.
*/
char				*multiplyHalf(char *s)
{
	char			*return_str;
	unsigned char	carry_nbr = 0;

	if (_strcmp(s, "") == 0) {
		free(s);
		if (!(return_str = _strdup("5")))
			return NULL;
		return return_str;
	}
	if (!(return_str = (char*)malloc(1 + _strlen(s) + 1))) {
		free(s);
		return NULL;
	}
	return_str[1 + _strlen(s)] = '\0';
	for (size_t i = _strlen(s) - 1 ; i != (size_t)-1 ; --i) {
		return_str[i + 1] = ((s[i] - '0') * 5 % 10 + carry_nbr) + '0';
		carry_nbr = (return_str[i + 1] - '0') / 10;
		carry_nbr += (s[i] - '0') * 5 / 10;
	}
	return_str[0] = carry_nbr + '0';
	free(s);
	return return_str;
}

char			*add(char *s1, char *s2)
{
	char		*return_str;
	size_t		len = _max_size(_strlen(s1), _strlen(s2));

	if (!(return_str = (char*)_calloc(len + 1, sizeof(char))))
		return NULL;
	for (size_t i = len - 1 ; i != (size_t)-1 ; --i) {
		if (i >= _strlen(s1))
			return_str[i] = s2[i];
		else if (i >= _strlen(s2))
			return_str[i] = s1[i];
		else {
			return_str[i] += (s1[i] - '0') + (s2[i] - '0') + '0';
			if (return_str[i] >= 10 + '0') {
				return_str[i] -= 10;
				++return_str[i - 1]; // The sum of fraction cannot be exceed 1, so it is safe.
			}
		}
	}
	free(s1);
	return return_str;	
}

char			*fraction2decimal(unsigned fraction)
{
	char		*decimal;
	char		*return_str;

	decimal = _strdup("");
	return_str = _strdup("");
	for (unsigned i = 22 ; i != (unsigned)-1 ; --i)
	{
		if (!(decimal = multiplyHalf(decimal)))
			return NULL;
		if (getBitFromUnsigned(fraction, i))
		{
			printf("%s\n", return_str);
			printf("%s\n", decimal);
			return_str = add(return_str, decimal);
			printf("%s\n", return_str);
			printf("\n");
			fflush(stdout);
		}
	}
	return return_str;
}

/*static bool		getBitFromUnsigned(unsigned u, unsigned n)
{
	return (bool)((u & (0b1 << n)) >> n);
}*/

/* f2s */

/*static char		*truncateSharp(char *s)
{
	char		*return_str;
	size_t		start = 0;

	while (s[start] == '#')
		++start;
	if (!(return_str = _strdup(s + start)))
		return NULL;
	free(s);
	return return_str;
}*/

static char		*multiplyTwo(char *s)
{
	char			*return_str;
	unsigned char	carry_nbr = 0;

	if (!(return_str = (char*)malloc(1 + _strlen(s) + 1))) {
		free(s);
		return NULL;
	}
	return_str[0] = '#';
	return_str[1 + _strlen(s)] = '\0';
	for (size_t i = _strlen(s) - 1 ; i != (size_t)-1 ; --i) {
		if (s[i] == '.') {
			return_str[i + 1] = '.';
			continue ;
		}
		return_str[i + 1] = ((s[i] - '0') * 2 % 10 + carry_nbr) + '0';
		carry_nbr = (return_str[i + 1] - '0') / 10;
		carry_nbr += (s[i] - '0') * 2 / 10;
	}
	if (carry_nbr)
		return_str[0] = carry_nbr + '0';
	return truncateSharp(return_str);
}

char			*f2s(SConversion *conversion_info, SFloat *sf)
{
	char		*fraction_decimal;

	fraction_decimal = fraction2decimal(sf->fraction); // 소수점 십진수화 할 때 까지는 fg 윗단에 놔야 될듯
	if (sf->exponent == 0)
		fraction_decimal = _strjoin("0.", fraction_decimal);
	else
		fraction_decimal = _strjoin("1.", fraction_decimal);
	if (sf->exponent == 0)
		sf->exponent = 1;
	if (sf->exponent > BIAS) {
		for (unsigned i = 0 ; i < sf->exponent - BIAS ; ++i) {
			printf("%s\n", fraction_decimal);
			fraction_decimal = multiplyTwo(fraction_decimal);
		}
	} else {
		for (unsigned i = 0 ; i < BIAS - sf->exponent ; ++i)
		{
			char **map = _split(fraction_decimal, '.');
			map[1] = multiplyHalf(map[1]);
			if (_strcmp(map[0], "1") == 0) {
				map[0][0] = '0';
				map[1] = add(map[1], "5");
			}
			fraction_decimal = _strjoin(_strjoin(map[0], "."), map[1]);
		}
	}
	if (sf->sign)
		fraction_decimal = _strjoin("-", fraction_decimal);
	printf("%s\n", fraction_decimal);
	(void)conversion_info;
	return fraction_decimal;
}