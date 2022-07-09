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
	"Ensure dont save variable name and return 1 if failure");
}

Test(var, validate_var_name_middle)
{
	t_env	*last_var = NULL;
	char	*cmd = {"VAR1*VAR2=/bin/bash"};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_eq(result, FAILURE,
	"Ensure dont save variable name and return 1 if failure");
}

Test(var, validate_var_name_last)
{
	t_env	*last_var = NULL;
	char	*cmd = {"VAR_1!=/bin/bash"};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_eq(result, FAILURE,
	"Ensure dont save variable name and return 1 if failure");
}

Test(var, validate_var_name_first_num)
{
	t_env	*last_var = NULL;
	char	*cmd = {"1_MINISHELL=/bin/bash"};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_eq(result, FAILURE,
	"Ensure dont save variable name and return 1 if failure");
}
