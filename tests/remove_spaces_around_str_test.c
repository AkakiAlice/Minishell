#include <criterion/criterion.h>
#include "minishell.h"

Test(remove_spaces_around_str, ptr_null)
{
	char	*str = NULL;
	char	*new_str;

	new_str = remove_spaces_around_str(str);
	cr_expect_null(new_str, "Ensure return null if pointer string is null");
	if (new_str != NULL)
		free(new_str);
}

Test(remove_spaces_around_str, spaces_around_str)
{
	char	*str = {"       MINISHELL=/bin/bash   "};
	char	*new_str;

	new_str = remove_spaces_around_str(str);
	cr_expect_str_eq(new_str, "MINISHELL=/bin/bash",
		"Ensure return string without spaces around word");
	if (new_str != NULL)
		free(new_str);
}

Test(remove_spaces_around_str, spaces_middle_str)
{
	char	*str = {"       MINISHELL='/bin  /bash'   "};
	char	*new_str;

	new_str = remove_spaces_around_str(str);
	cr_expect_str_eq(new_str, "MINISHELL='/bin  /bash'",
		"Ensure return string without spaces around word and not space inside the word");
	if (new_str != NULL)
		free(new_str);
}
