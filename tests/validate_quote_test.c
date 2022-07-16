#include <criterion/criterion.h>
#include "minishell.h"

Test(validate_quote_closed, single_quote_unclosed)
{
	char	*str = {"te''s""t'e"};
	bool	result;

	result = validate_quote_closed(str);
	cr_expect_eq(result, false,
		"Ensure returns false if the single quotes are open");
}

Test(validate_quote_closed, single_quote_closed)
{
	char	*str = {"te's\"t'e"};
	bool	result;

	result = validate_quote_closed(str);
	cr_expect_eq(result, true,
		"Ensure returns true if the single quotes are closed");
}

Test(validate_quote_closed, double_quote_unclosed)
{
	char	*str = {"te\"\"s't\"e"};
	bool	result;

	result = validate_quote_closed(str);
	cr_expect_eq(result, false,
		"Ensure returns false if the double quotes are open");
}

Test(validate_quote_closed, double_quote_closed)
{
	char	*str = {"te\"s''t\"e"};
	bool	result;

	result = validate_quote_closed(str);
	cr_expect_eq(result, true,
		"Ensure returns true if the double quotes are closed");
}

Test(validate_quote_closed, advanced_1)
{
	char	*str = {"'\"'\""};
	bool	result;

	result = validate_quote_closed(str);
	cr_expect_eq(result, false,
		"Ensure returns false if the quotes are open");
}

Test(validate_quote_closed, advanced_2)
{
	char	*str = {"ex\"em'plo\"\"\"'"};
	bool	result;

	result = validate_quote_closed(str);
	cr_expect_eq(result, false,
		"Ensure returns false if the quotes are open");
}

Test(validate_quote_closed, advanced_3)
{
	char	*str = {"ex\"em'plo\"\"\"'\""};
	bool	result;

	result = validate_quote_closed(str);
	cr_expect_eq(result, false,
		"Ensure returns false if the quotes are open");
}

Test(validate_quote_closed, advanced_4)
{
	char	*str = {"ex\"o\"'\"d\"'"};
	bool	result;

	result = validate_quote_closed(str);
	cr_expect_eq(result, true,
		"Ensure returns false if the quotes are closed");
}

Test(str_without_quotes, simple_quote)
{
	char	*str = {"tes'ter'"};
	char	*result;

	result = str_without_quotes(str);
	cr_expect_str_eq(result, "tester",
		"Ensure returns string without quotes");
	free(result);
}

Test(str_without_quotes, double_quote)
{
	char	*str = {"tes\"ter\""};
	char	*result;

	result = str_without_quotes(str);
	cr_expect_str_eq(result, "tester",
		"Ensure returns string without quotes");
	free(result);
}

Test(str_without_quotes, without_char_outside_quotes)
{
	char	*str = {"'minishell'"};
	char	*result;

	result = str_without_quotes(str);
	cr_expect_str_eq(result, "minishell",
		"Ensure returns string without quotes");
	free(result);
}

Test(str_without_quotes, advanced_1)
{
	char	*str = {"'mini''''shell'"};
	char	*result;

	result = str_without_quotes(str);
	cr_expect_str_eq(result, "minishell",
		"Ensure returns string without quotes");
	free(result);
}

Test(str_without_quotes, advanced_2)
{
	char	*str = {"'mini'' 'shell"};
	char	*result;

	result = str_without_quotes(str);
	cr_expect_str_eq(result, "mini shell",
		"Ensure returns string without quotes");
	free(result);
}

Test(check_var_expansion, single_quotes)
{
	char	*str = {"'$HOME'"};
	bool	result;

	result = check_var_expansion(str);
	cr_expect_eq(result, false,
		"Ensure returns false if variable expansion in single quotes");
}

Test(check_var_expansion, double_quotes)
{
	char	*str = {"\"$HOME\""};
	bool	result;

	result = check_var_expansion(str);
	cr_expect_eq(result, true,
		"Ensure returns true if variable expansion in double quotes");
}

Test(check_var_expansion, advanced_1)
{
	char	*str = {"\"Hello\"'$HOME'"};
	bool	result;

	result = check_var_expansion(str);
	cr_expect_eq(result, false,
		"Ensure returns false if variable expansion in single quotes");
}
