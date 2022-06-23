#include <criterion/criterion.h>
#include "minishell.h"

Test(env_lst_add_back, add_empty_list)
{
	t_env	*last_env = NULL;
	int		result;

	result = env_lst_add_back(&last_env);
	cr_expect_null(last_env->name, "Ensure create node with name");
	cr_expect_null(last_env->value, "Ensure create node with value");
	cr_expect_eq(result, EXIT_SUCCESS, "Ensure return 1 if success");
	free(last_env->name);
	free(last_env->value);
	free(last_env);
}

Test(env_lst_add_back, add_list_with_node)
{
	t_env	*last_env = NULL;
	int		result;
	t_env	*temp;
	t_env	*current;

	env_lst_add_back(&last_env);
	env_lst_add_back(&last_env);
	result = env_lst_add_back(&last_env);
	cr_expect_null(last_env->name, "Ensure create node with name");
	cr_expect_null(last_env->value, "Ensure create node with value");
	cr_expect_null(last_env->next->name,
	"Ensure create node with name and insertion at the end of the list and change pointer to last node");
	cr_expect_null(last_env->next->value, "Ensure create node with value and insertion at the end of the list and change pointer to last node");
	cr_expect_null(last_env->next->next->name, "Ensure create node with name and insertion at the end of the list and change pointer to last node");
	cr_expect_null(last_env->next->next->value, "Ensure create node with value and insertion at the end of the list and change pointer to last node");
	cr_expect_eq(result, EXIT_SUCCESS, "Ensure return 1 if success");
	current = last_env->next;
	while (current != last_env)
	{
		free(current->name);
		free(current->value);
		temp = current->next;
		free(current);
		current = temp;
	}
	free(last_env->name);
	free(last_env->value);
	free(last_env);
}

Test(env, save_env_name)
{
	t_env	*last_env = NULL;
	char	**envp;
	t_env	*temp;
	t_env	*current;

	envp = malloc(sizeof(char *) * 3);
	envp[0] = strdup("SHELL=/bin/bash");
	envp[1] = strdup("SESSION_MANAGER=local/PC-LL750HS6W:@/tmp/.ICE-unix/1888");
	envp[2] = NULL;
	save_env(&last_env, envp);
	cr_expect_str_eq(last_env->next->name, "SHELL", "Ensure save environment name");
	cr_expect_str_eq(last_env->name, "SESSION_MANAGER", "Ensure save multiple environment name");
	current = last_env->next;
	while (current != last_env)
	{
		free(current->name);
		free(current->value);
		temp = current->next;
		free(current);
		current = temp;
	}
	free(last_env->name);
	free(last_env->value);
	free(last_env);
	ft_matrix_free(envp);
}
