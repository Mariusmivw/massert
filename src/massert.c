/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   massert.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 22:26:01 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/18 22:26:09 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "massert.h"

bool	bool_eq(intmax_t a, intmax_t b)
{
	return ((a != false) == (b != false));
}

char	*bool_str(intmax_t p)
{
	if (p == false)
		return (strdup("false"));
	return (strdup("true"));
}

bool	char_eq(intmax_t a, intmax_t b)
{
	char a_ = (char)a;
	char b_ = (char)b;
	return (a_ == b_);
}

char	*char_str(intmax_t p)
{
	char c = (char)p;
	char *dst = malloc((11) * sizeof(char));
	snprintf(dst, 11, "'%c' (%hhi)", c, c);
	return (dst);
}

char	*inverse_char_str(intmax_t p)
{
	char c = (char)p;
	char *dst = malloc((11) * sizeof(char));
	snprintf(dst, 11, "%hhi ('%c')", c, c);
	return (dst);
}

bool	signed_char_eq(intmax_t a, intmax_t b)
{
	signed char a_ = (signed char)a;
	signed char b_ = (signed char)b;
	return (a_ == b_);
}

char	*signed_char_str(intmax_t p)
{
	signed char c = (signed char)p;
	char *dst = malloc((11) * sizeof(char));
	snprintf(dst, 11, "'%c' (%hhi)", c, c);
	return (dst);
}

char	*inverse_signed_char_str(intmax_t p)
{
	signed char c = (signed char)p;
	char *dst = malloc((11) * sizeof(char));
	snprintf(dst, 11, "%hhi ('%c')", c, c);
	return (dst);
}

bool	unsigned_char_eq(intmax_t a, intmax_t b)
{
	unsigned char a_ = (unsigned char)a;
	unsigned char b_ = (unsigned char)b;
	return (a_ == b_);
}

char	*unsigned_char_str(intmax_t p)
{
	unsigned char c = (unsigned char)p;
	char *dst = malloc((11) * sizeof(char));
	snprintf(dst, 11, "'%c' (%hhi)", c, c);
	return (dst);
}

char	*inverse_unsigned_char_str(intmax_t p)
{
	unsigned char c = (unsigned char)p;
	char *dst = malloc((11) * sizeof(char));
	snprintf(dst, 11, "%hhu ('%c')", c, c);
	return (dst);
}

bool	signed_eq(intmax_t a, intmax_t b)
{
	intmax_t a_ = (intmax_t)a;
	intmax_t b_ = (intmax_t)b;
	return (a_ == b_);
}

char	*signed_str(intmax_t p)
{
	intmax_t i = (intmax_t)p;
	int len = snprintf(NULL, 0, "%ji", i);
	char *dst = malloc(len + 1);
	snprintf(dst, len + 1, "%ji", i);
	return (dst);
}

bool	unsigned_eq(intmax_t a, intmax_t b)
{
	uintmax_t a_ = (uintmax_t)a;
	uintmax_t b_ = (uintmax_t)b;
	return (a_ == b_);
}

char	*unsigned_str(intmax_t p)
{
	uintmax_t i = (uintmax_t)p;
	int len = snprintf(NULL, 0, "%ju", i);
	char *dst = malloc(len + 1);
	snprintf(dst, len + 1, "%ju", i);
	return (dst);
}

bool	float_eq(intmax_t a, intmax_t b)
{
	long double a_ = (long double)a;
	long double b_ = (long double)b;
	return (a_ == b_);
}

char	*float_str(intmax_t p)
{
	long double i = (long double)p;
	int len = snprintf(NULL, 0, "%Lf", i);
	char *dst = malloc(len + 1);
	snprintf(dst, len + 1, "%Lf", i);
	return (dst);
}

bool	str_eq(intmax_t a, intmax_t b)
{
	return (strcmp((char *)a, (char *)b) == 0);
}

char	*str_str(intmax_t p)
{
	int len = strlen((char *)p);
	char *dst = malloc((len + 2 + 1) * sizeof(char));
	snprintf(dst, len + 2 + 1, "\"%s\"", (char *)p);
	return (dst);
}

bool	ptr_eq(intmax_t a, intmax_t b)
{
	void *a_ = (void *)a;
	void *b_ = (void *)b;
	return (a_ == b_);
}

char	*ptr_str(intmax_t p)
{
	void *i = (void *)p;
	int len = snprintf(NULL, 0, "%p", i);
	char *dst = malloc(len + 1);
	snprintf(dst, len + 1, "%p", i);
	return (dst);
}
