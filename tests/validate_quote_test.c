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
