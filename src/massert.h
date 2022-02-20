#ifndef MASSERT_H
# define MASSERT_H

// Setup
# if 1
#  include <stdio.h>
#  include <stdlib.h>
#  include <unistd.h>
#  include <string.h>
#  include <stdint.h>
#  include <stdbool.h>

#  undef true
#  undef false
#  define true (bool)1
#  define false (bool)0

typedef char	*(*t_massert_str_fn)(intmax_t data);
typedef bool	(*t_massert_eq_fn)(intmax_t a, intmax_t b);
typedef struct assert_list_s {
	char				*type_syntax;
	t_massert_str_fn	as_str;
	t_massert_eq_fn		is_eq;
}	assert_list_t;

#  define pragma(p) _Pragma(#p)

#  define ignore_gcc_error(p) pragma(GCC diagnostic ignored p)
/**
 * Usage: `add_assert_type(void *, compare_ptrs, ptr_as_str)`
 * It is recommended to not add structs as types, you should use pointers to structs instead
 * @param type The type to add a definition for
 * @param eq_fn The function (t_massert_eq_fn) which checks whether the two inputs are the same
 * @param str_fn The function (t_massert_str_fn) to convert the argument to a (c) string
 */
#  define add_assert_type(type, eq_fn, str_fn) , type: (assert_list_t){.type_syntax = #type, .as_str = str_fn, .is_eq = eq_fn}
#  define assert_get_type(x) _Generic((x), default: (assert_list_t){.type_syntax = NULL} assert_types)
#  define assert_msg(format, ...) dprintf(STDERR_FILENO, "%s:%i: %s: " format, __FILE__, __LINE__, __func__, __VA_ARGS__); abort()

#  ifndef custom_assert_types
/**
 * Add your own types by using the `add_assert_types(type, eq_fn, str_fn)` (each call seperated by whitespace)
 */
#   define custom_assert_types
#  endif
# endif

// Config
# if 1
#  define ignore_gcc_errors				\
	ignore_gcc_error("-Wall")			\
	ignore_gcc_error("-Wextra")			\
	ignore_gcc_error("-Wconversion")

#  define assert_types															\
	custom_assert_types															\
																				\
	add_assert_type(bool, bool_eq, bool_str)									\
																				\
	add_assert_type(char, char_eq, char_str)									\
	add_assert_type(signed char, signed_char_eq, signed_char_str)				\
	add_assert_type(unsigned char, unsigned_char_eq, unsigned_char_str)			\
																				\
	/* add_assert_type(char, char_eq, inverse_char_str) */							\
	/* add_assert_type(signed char, signed_char_eq, inverse_signed_char_str) */		\
	/* add_assert_type(unsigned char, unsigned_char_eq, inverse_unsigned_char_str) */	\
																				\
	add_assert_type(short int, signed_eq, signed_str)							\
	add_assert_type(unsigned short int, unsigned_eq, unsigned_str)				\
																				\
	add_assert_type(int, signed_eq, signed_str)									\
	add_assert_type(unsigned int, unsigned_eq, unsigned_str)					\
																				\
	add_assert_type(long, signed_eq, signed_str)								\
	add_assert_type(unsigned long, unsigned_eq, unsigned_str)					\
																				\
	add_assert_type(long long, signed_eq, signed_str)							\
	add_assert_type(unsigned long long, unsigned_eq, unsigned_str)				\
																				\
	add_assert_type(float, float_eq, float_str)									\
	add_assert_type(double, float_eq, float_str)								\
	add_assert_type(long double, float_eq, float_str)							\
																				\
	add_assert_type(char *, str_eq, str_str)									\
																				\
	add_assert_type(void *, ptr_eq, ptr_str)
# endif

# if 1
bool	bool_eq(intmax_t a, intmax_t b);
char	*bool_str(intmax_t p);
bool	char_eq(intmax_t a, intmax_t b);
char	*char_str(intmax_t p);
char	*inverse_char_str(intmax_t p);
bool	signed_char_eq(intmax_t a, intmax_t b);
char	*signed_char_str(intmax_t p);
char	*inverse_signed_char_str(intmax_t p);
bool	unsigned_char_eq(intmax_t a, intmax_t b);
char	*unsigned_char_str(intmax_t p);
char	*inverse_unsigned_char_str(intmax_t p);
bool	signed_eq(intmax_t a, intmax_t b);
char	*signed_str(intmax_t p);
bool	unsigned_eq(intmax_t a, intmax_t b);
char	*unsigned_str(intmax_t p);
bool	float_eq(intmax_t a, intmax_t b);
char	*float_str(intmax_t p);
bool	str_eq(intmax_t a, intmax_t b);
char	*str_str(intmax_t p);
bool	ptr_eq(intmax_t a, intmax_t b);
char	*ptr_str(intmax_t p);
# endif

// Assert
# if 1
#  define do_massert(type, a, b, a_input, b_input)						\
{																		\
	char	*a_str;														\
	char	*b_str;														\
	int		len1;														\
	int		len2;														\
	int		len;														\
	intmax_t	a_value = (intmax_t)a;									\
	intmax_t	b_value = (intmax_t)b;									\
	if (!type.is_eq(a_value, b_value))									\
	{																	\
		a_str = type.as_str(a_value);									\
		b_str = type.as_str(b_value);									\
		len1 = strlen(a_str);											\
		len2 = strlen(a_input);											\
		len = len1 > len2 ? len1 : len2;								\
		assert_msg("Assertion failed:\n%*s == %s:\n%*s == %s\n",		\
			len, a_input, b_input,										\
			len, a_str, b_str);											\
	}																	\
}

#  define massert_compare(a, b)													\
{																				\
	pragma(GCC diagnostic push)													\
	ignore_gcc_errors															\
																				\
	char	*DEBUG_VALUE_INPUT_NAME = #a;										\
	char	*DEBUG_EXPECT_INPUT_NAME = #b;										\
																				\
	assert_list_t a_type = assert_get_type(a);									\
	assert_list_t b_type = assert_get_type(b);									\
																				\
	if (a_type.type_syntax == NULL && b_type.type_syntax == NULL)				\
	{																			\
		assert_msg("Cannot detect type of <%s> and <%s>\n",						\
			DEBUG_VALUE_INPUT_NAME, DEBUG_EXPECT_INPUT_NAME);					\
		abort();																\
	}																			\
	if (a_type.type_syntax == NULL)												\
	{																			\
		assert_msg("Cannot detect type of <%s>\n",								\
			DEBUG_VALUE_INPUT_NAME);											\
		abort();																\
	}																			\
	if (a_type.type_syntax == NULL && b_type.type_syntax == NULL)				\
	{																			\
		assert_msg("Cannot detect type of <%s>\n",								\
			DEBUG_EXPECT_INPUT_NAME);											\
		abort();																\
	}																			\
	if (strcmp(a_type.type_syntax, b_type.type_syntax) != 0)					\
	{																			\
		assert_msg("Cannot compare types <%s> and <%s>\n",						\
			a_type.type_syntax, b_type.type_syntax);							\
		abort();																\
	}																			\
	do_massert(a_type, a, b, DEBUG_VALUE_INPUT_NAME, DEBUG_EXPECT_INPUT_NAME);	\
																				\
	pragma(GCC diagnostic pop)													\
}

/**
 * Trigger abort when the two values are different
 * You can add your own types by defining `custom_assert_types`
 */
#  define massert(value1, value2)												\
{																				\
	massert_compare(value1, value2);											\
}
# endif

#endif
