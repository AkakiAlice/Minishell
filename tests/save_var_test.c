#include <criterion/criterion.h>
#include "minishell.h"

Test(save_var, save_var_name)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINISHELL=/bin/bash"};

	save_var(&last_var, cmd);
	cr_expect_str_eq(last_var->name, "MINISHELL", "Ensure save variable name");
	free_env_lst(&last_var);
}

Test(save_var, save_var_value)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINI_SHELL=/bin/bash"};

	save_var(&last_var, cmd);
	cr_expect_str_eq(last_var->value, "/bin/bash", "Ensure save variable value");
	free_env_lst(&last_var);
}

Test(save_var, save_var_multi_value)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINI_SHELL=/bin/bash:/bin/sh"};

	save_var(&last_var, cmd);
	cr_expect_str_eq(last_var->value, "/bin/bash:/bin/sh",
		"Ensure save multiple variable value");
	free_env_lst(&last_var);
}

Test(save_var, not_equal_sign)
{
	t_env	*last_var = NULL;
	char	*cmd = {"MINISHELL"};
	int		result;

	result = save_var(&last_var, cmd);
	cr_expect_eq(result, FAILURE,
	"Ensure dont save variable without equal sign and return 1 if failure");
}

Test(save_var, space_before_var)
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

Test(save_var, space_after_var)
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

Test(save_var, var_empty)
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

Test(save_var, var_empty_with_spaces)
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

Test(save_var, var_multiple_equal_sign)
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
