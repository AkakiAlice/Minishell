#include <criterion/criterion.h>
#include "minishell.h"

Test(validate_var, var_name_start)
{
	char	*var_name = {"-VAR"};
	char	*var_value = {"/bin/bash"};
	bool	result;

	result = validate_var(var_name, var_value);
	cr_expect_eq(result, false,
	"Ensure returns false if the variable name with - character");
}

Test(validate_var, var_name_middle)
{
	char	*var_name = {"VAR1*VAR2"};
	char	*var_value = {"/bin/bash"};
	bool	result;

	result = validate_var(var_name, var_value);
	cr_expect_eq(result, false,
	"Ensure returns false if the variable name with * character");
}

Test(validate_var, var_name_last)
{
	char	*var_name = {"VAR_1!"};
	char	*var_value = {"/bin/bash"};
	bool	result;

	result = validate_var(var_name, var_value);
	cr_expect_eq(result, false,
	"Ensure returns false if the variable name with ! character");
}

Test(validate_var, var_name_first_num)
{
	char	*var_name = {"1_MINISHELL"};
	char	*var_value = {"/bin/bash"};
	bool	result;

	result = validate_var(var_name, var_value);
	cr_expect_eq(result, false,
		"Ensure returns false if the variable name with the first char is number");
}

Test(validate_var, space_between_equal)
{
	char	*var_name = {"MINISHELL "};
	char	*var_value = {" /bin/bash"};
	bool	result;

	result = validate_var(var_name, var_value);
	cr_expect_eq(result, false,
		"Ensure returns false if the variable with space between equal sign");
}

Test(validate_var, space_before_equal)
{
	char	*var_name = {"MINISHELL "};
	char	*var_value = {"/bin/bash"};
	bool	result;

	result = validate_var(var_name, var_value);
	cr_expect_eq(result, false,
		"Ensure returns false if the variable with space before equal sign");
}

Test(validate_var, space_after_equal)
{
	char	*var_name = {"MINISHELL"};
	char	*var_value = {" /bin/bash"};
	bool	result;

	result = validate_var(var_name, var_value);
	cr_expect_eq(result, false,
		"Ensure returns false if the variable with space after equal sign");
}

Test(validate_var, word_before_var)
{
	char	*var_name = {"ls  MINISHELL"};
	char	*var_value = {"/bin/bash"};
	bool	result;

	result = validate_var(var_name, var_value);
	cr_expect_eq(result, false,
		"Ensure returns false if the variable with word before variable declaration");
}

Test(validate_var, word_after_var)
{
	char	*var_name = {"MINISHELL"};
	char	*var_value = {"/bin/bash  ls"};
	bool	result;

	result = validate_var(var_name, var_value);
	cr_expect_eq(result, false,
		"Ensure returns false if the variable with word after variable declaration");
}

Test(validate_var, word_with_space)
{
	char	*var_name = {"MINISHELL"};
	char	*var_value = {"'/bin/bash ls'"};
	bool	result;

	result = validate_var(var_name, var_value);
	cr_expect_eq(result, true,
		"Ensure returns true if the variable value with space between quotes");
}

Test(validate_var, word_with_space_quotes)
{
	char	*var_name = {"MINISHELL"};
	char	*var_value = {"/bin/bash' 'ls"};
	bool	result;

	result = validate_var(var_name, var_value);
	cr_expect_eq(result, true,
		"Ensure returns true if the variable value with space between quotes");
}

Test(validate_var, space_outside_quotes_1)
{
	char	*var_name = {"MINISHELL"};
	char	*var_value = {"   /bin/bash' 'ls"};
	bool	result;

	result = validate_var(var_name, var_value);
	cr_expect_eq(result, false,
		"Ensure returns false if the variable value with space outside quotes");
}

Test(validate_var, space_outside_quotes_2)
{
	char	*var_name = {"MINISHELL"};
	char	*var_value = {"/bin/bash' 'ls    -a"};
	bool	result;

	result = validate_var(var_name, var_value);
	cr_expect_eq(result, false,
		"Ensure returns false if the variable value with space outside quotes");
}

Test(validate_var, space_outside_quotes_3)
{
	char	*var_name = {"MINISHELL"};
	char	*var_value = {"   /bin/bash' 'ls    -a"};
	bool	result;

	result = validate_var(var_name, var_value);
	cr_expect_eq(result, false,
		"Ensure returns false if the variable value with space outside quotes");
}

Test(validate_var, space_outside_quotes_4)
{
	char	*var_name = {"MINISHELL"};
	char	*var_value = {"/bin/bash' 'ls  \"-a\""};
	bool	result;

	result = validate_var(var_name, var_value);
	cr_expect_eq(result, false,
		"Ensure returns false if the variable value with space outside quotes");
}
