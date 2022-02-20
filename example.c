#include "massert.h"

typedef struct s_string {
	char	*data;
	size_t	len;
}	t_string;

bool	strings_eq(intmax_t s1, intmax_t s2)
{
	t_string *_s1 = s1;
	t_string *_s2 = s2;
	if (_s1->len != _s2->len)
		return (false);
	return (strncmp(_s1->data, _s2->data, _s1->len) == 0);
}

char	*string_as_c_str(intmax_t s1)
{
	t_string *_s1 = s1;
	char *res = malloc((_s1->len + 1) * sizeof(char));
	res[_s1->len] = '\0';
	memcpy(res, _s1->data, _s1->len);
	return (res);
}

#define custom_assert_types		\
	add_assert_type(t_string *, strings_eq, string_as_c_str)

int main(void)
{
	t_string	str1 = {.data = "hello", .len = 4};
	t_string	str2 = {.data = "hello", .len = 5};;
	massert(&str1, &str2);
	return (0);
}
