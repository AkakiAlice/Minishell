#include <criterion/criterion.h>
#include "minishell.h"

Test(remove_spaces_outside_quote, ptr_null)
{
	char	*str = NULL;
	char	*new_str;

	new_str = remove_spaces_outside_quote(str);
	cr_expect_null(new_str, "Ensure return null if pointer string is null");
	if (new_str != NULL)
		free(new_str);
}

Test(remove_spaces_outside_quote, spaces_str)
{
	char	*str = {"  ls  | cat | ls"};
	char	*new_str;

	new_str = remove_spaces_outside_quote(str);
	cr_expect_str_eq(new_str, "ls|cat|ls",
		"Ensure return string without spaces");
	if (new_str != NULL)
		free(new_str);
}

Test(remove_spaces_outside_quote, spaces_str_quotes)
{
	char	*str = {"  ls  |'  cat  '| ls"};
	char	*new_str;

	new_str = remove_spaces_outside_quote(str);
	cr_expect_str_eq(new_str, "ls|'  cat  '|ls",
		"Ensure return string with space in single quotes");
	if (new_str != NULL)
		free(new_str);
}

Test(remove_spaces_outside_quote, spaces_str_quotes_multiple)
{
	char	*str = {"\"  ls '   ' \"|'  cat  '| \"   ls\"       "};
	char	*new_str;

	new_str = remove_spaces_outside_quote(str);
	cr_expect_str_eq(new_str, "\"  ls '   ' \"|'  cat  '|\"   ls\"",
		"Ensure return string with space in single quotes");
	if (new_str != NULL)
		free(new_str);
}
