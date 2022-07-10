#include <criterion/criterion.h>
#include "minishell.h"

Test(var, save_var_name)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINISHELL=/bin/bash"};

	save_var(&last_var, cmd);
	cr_expect_str_eq(last_var->name, "MINISHELL", "Ensure save variable name");
	free_env_lst(&last_var);
}

Test(var, save_var_value)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINI_SHELL=/bin/bash"};

	save_var(&last_var, cmd);
	cr_expect_str_eq(last_var->value, "/bin/bash", "Ensure save variable value");
	free_env_lst(&last_var);
}

Test(var, save_var_multi_value)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINI_SHELL=/bin/bash:/bin/sh"};

	save_var(&last_var, cmd);
	cr_expect_str_eq(last_var->value, "/bin/bash:/bin/sh",
		"Ensure save multiple variable value");
	free_env_lst(&last_var);
}

Test(var, validate_var_name_start)
{
	t_env	*last_var = NULL;
	char	*cmd = {"-VAR=/bin/bash"};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_eq(result, FAILURE,
	"Ensure dont save variable name with - character and return 1 if failure");
}

Test(var, validate_var_name_middle)
{
	t_env	*last_var = NULL;
	char	*cmd = {"VAR1*VAR2=/bin/bash"};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_eq(result, FAILURE,
	"Ensure dont save variable name with * character and return 1 if failure");
}

Test(var, validate_var_name_last)
{
	t_env	*last_var = NULL;
	char	*cmd = {"VAR_1!=/bin/bash"};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_eq(result, FAILURE,
	"Ensure dont save variable name with ! character and return 1 if failure");
}

Test(var, validate_var_name_first_num)
{
	t_env	*last_var = NULL;
	char	*cmd = {"1_MINISHELL=/bin/bash"};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_eq(result, FAILURE,
	"Ensure dont save variable name with the first char being number and return 1 if failure");
}

Test(var, not_equal_sign)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINISHELL"};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_eq(result, FAILURE,
	"Ensure dont save variable without equal sign and return 1 if failure");
}

Test(var, space_between_equal)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINISHELL = /bin/bash"};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_eq(result, FAILURE,
	"Ensure dont save variable with space between equal sign and return 1 if failure");
}

Test(var, space_before_equal)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINISHELL =/bin/bash"};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_eq(result, FAILURE,
	"Ensure dont save variable with space before equal sign and return 1 if failure");
}

Test(var, space_after_equal)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINISHELL= /bin/bash"};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_eq(result, FAILURE,
	"Ensure dont save variable with space after equal sign and return 1 if failure");
}

Test(var, word_before_var)
{
	t_env	*last_var = NULL;
	char	*cmd = {"ls  MINISHELL=/bin/bash"};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_eq(result, FAILURE,
	"Ensure dont save variable with word before variable declaration and return 1 if failure");
}

Test(var, word_after_var)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINISHELL=/bin/bash  ls"};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_eq(result, FAILURE,
	"Ensure dont save variable with word after variable declaration and return 1 if failure");
}

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

Test(var, space_before_var)
{
	t_env	*last_var = NULL;
	char	*cmd = {"       MINISHELL=/bin/bash"};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_str_eq(last_var->name, "MINISHELL",
		"Ensure save variable name without space");
	cr_expect_eq(result, SUCCESS, "Ensure return 0 if success");
	free_env_lst(&last_var);
}

Test(var, space_after_var)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINISHELL=/bin/bash      "};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_str_eq(last_var->value, "/bin/bash",
		"Ensure save variable value without space");
	cr_expect_eq(result, SUCCESS, "Ensure return 0 if success");
	free_env_lst(&last_var);
}

Test(var, var_empty)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINISHELL="};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_str_eq(last_var->value, "",
		"Ensure save variable value as empty");
	cr_expect_eq(result, SUCCESS, "Ensure return 0 if success");
	free_env_lst(&last_var);
}

Test(var, var_empty_with_spaces)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINISHELL=     "};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_str_eq(last_var->value, "",
		"Ensure save variable value as empty");
	cr_expect_eq(result, SUCCESS, "Ensure return 0 if success");
	free_env_lst(&last_var);
}

Test(var, var_multiple_equal_sign)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINISHELL=="};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_str_eq(last_var->value, "=",
		"Ensure save variable value as equal");
	cr_expect_eq(result, SUCCESS, "Ensure return 0 if success");
	free_env_lst(&last_var);
}

Test(is_quote, not_signal)
{
	char	*cmd = {"MINISHELL="};
	int		result;

	result = is_quote(cmd);
	cr_expect_eq(result, -1,
		"Ensure returns -1 if the command not contain quotes");
}

Test(is_quote, simple_quote)
{
	char	*cmd = {"MINISHELL=ok'"};
	int		result;

	result = is_quote(cmd);
	cr_expect_eq(result, S_QUOTE,
		"Ensure returns 39 if the command contain simple quote");
}

Test(is_quote, double_quote)
{
	char	*cmd = {"MINISHELL=ok\""};
	int		result;

	result = is_quote(cmd);
	cr_expect_eq(result, D_QUOTE,
		"Ensure returns 34 if the command contain double quote");
}

Test(count_char, simple_quote)
{
	char	*cmd = {"MINISHELL=te''st'e"};
	int		count;

	count = count_char(cmd, S_QUOTE);
	cr_expect_eq(count, 3,
		"Ensure returns the numbers of single quotes");
}

Test(count_char, double_quote)
{
	char	*cmd = {"MINISHELL=te\"\"st\"e"};
	int		count;

	count = count_char(cmd, D_QUOTE);
	cr_expect_eq(count, 3,
		"Ensure returns the numbers of double quotes");
}

Test(count_char, mix_quote)
{
	char	*cmd = {"MINISHELL=te''s""t'e"};
	int		count;

	count = count_char(cmd, S_QUOTE);
	cr_expect_eq(count, 3,
		"Ensure returns the numbers of single quotes");
}

Test(validate_quote_closed, single_quote_unclosed)
{
	char	*str = {"te''s""t'e"};
	int		result;

	result = validate_quote_closed(str);
	cr_expect_eq(result, FAILURE,
		"Ensure returns 1 if the single quotes are unclosed");
}

Test(validate_quote_closed, single_quote_closed)
{
	char	*str = {"te's\"t'e"};
	int		result;

	result = validate_quote_closed(str);
	cr_expect_eq(result, SUCCESS,
		"Ensure returns 0 if the single quotes are closed");
}

Test(validate_quote_closed, double_quote_unclosed)
{
	char	*str = {"te\"\"s't\"e"};
	int		result;

	result = validate_quote_closed(str);
	cr_expect_eq(result, FAILURE,
		"Ensure returns 1 if the double quotes are unclosed");
}

Test(validate_quote_closed, double_quote_closed)
{
	char	*str = {"te\"s''t\"e"};
	int		result;

	result = validate_quote_closed(str);
	cr_expect_eq(result, SUCCESS,
		"Ensure returns 0 if the double quotes are closed");
}
