#include <criterion/criterion.h>
#include "libft.h"

char	*str = NULL;
char	char_split = ' ';
char	**result = NULL;

void	suite_setup(void)
{
	str = "Hey MarVin!";
	return ;
}

TestSuite(split, .init=suite_setup);

Test(split, create) {
	int	i;

	result = ft_split(str, char_split);
	cr_assert(result, "Ensure split string with space");
	cr_expect_str_eq(result[0], "Hey", "Ensure split string with space, index = 0");
	cr_expect_str_eq(result[1], "MarVin!", "Ensure split string with space, index = 1");
	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

Test(split, str_null) {
	str = "\0";
	result = ft_split(str, char_split);
	cr_assert(result, "Ensure returns NULL if string is empty");
}
