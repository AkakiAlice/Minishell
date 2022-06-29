#include <criterion/criterion.h>
#include "libft.h"

Test(ft_strncmp_eq, is_equal)
{
	char	*s1 = {"|"};
	char	*s2 = {"|"};
	int		result;

	result = ft_strncmp_eq(s1, s2, 1);
	cr_expect_eq(result, 1, "Ensure return 1 if string is equal");
}
