#include <criterion/criterion.h>
#include "minishell.h"

Test(env_lst_add_back, add_empty_list)
{
	t_env	*last_env = NULL;
	int		result;

	result = env_lst_add_back(&last_env, strdup("SHELL"), strdup("/bin/bash"));
	cr_expect(last_env->name, "Ensure create node with name");
	cr_expect(last_env->value, "Ensure create node with value");
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

	env_lst_add_back(&last_env, strdup("SHELL"), strdup("/bin/bash"));
	env_lst_add_back(&last_env, strdup("SHELL"), strdup("/bin/bash"));
	result = env_lst_add_back(&last_env,strdup("SHELL"), strdup("/bin/bash"));
	cr_expect(last_env->name, "Ensure create node with name");
	cr_expect(last_env->value, "Ensure create node with value");
	cr_expect(last_env->next->name,
	"Ensure create node with name and insertion at the end of the list and change pointer to last node");
	cr_expect(last_env->next->value, "Ensure create node with value and insertion at the end of the list and change pointer to last node");
	cr_expect(last_env->next->next->name, "Ensure create node with name and insertion at the end of the list and change pointer to last node");
	cr_expect(last_env->next->next->value, "Ensure create node with value and insertion at the end of the list and change pointer to last node");
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

Test(env, get_env_value)
{
	char	*envp = {"SHELL=/bin/bash"};
	char	**split_env;
	char	*env_value;

	split_env = ft_split(envp, '=');
	env_value = get_env_value(envp, split_env[0]);
	cr_expect_str_eq(env_value, "/bin/bash", "Ensure get environment value");
	ft_matrix_free(split_env);
	free(env_value);
}

Test(env, save_multiple_env_value)
{
	t_env	*last_env = NULL;
	char	**envp;
	t_env	*temp;
	t_env	*current;

	envp = malloc(sizeof(char *) * 5);
	envp[0] = strdup("SHELL=/bin/bash");
	envp[1] = strdup("SESSION_MANAGER=local/PC-LL750HS6W:@/tmp/.ICE-unix/1888");
	envp[2] = strdup("PATH=/home/pmitsuko/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin");
	envp[3] = strdup("LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40");
	envp[4] = NULL;
	save_env(&last_env, envp);
	cr_expect_str_eq(last_env->value, "rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40", "Ensure save LS_COLORS value");
	cr_expect_str_eq(last_env->next->value, "/bin/bash", "Ensure save SHELL value");
	cr_expect_str_eq(last_env->next->next->value, "local/PC-LL750HS6W:@/tmp/.ICE-unix/1888", "Ensure save SESSION_MANAGER value");
	cr_expect_str_eq(last_env->next->next->next->value, "/home/pmitsuko/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", "Ensure save PATH value");
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
