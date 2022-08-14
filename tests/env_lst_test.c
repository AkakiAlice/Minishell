#include <criterion/criterion.h>
#include "minishell.h"

Test(env_lst_add_back, add_empty_list)
{
	t_env	*head_env = NULL;
	int		result;

	result = env_lst_add_back(&head_env, strdup("SHELL"), strdup("/bin/bash"));
	cr_expect(head_env->name, "Ensure create node with name");
	cr_expect(head_env->value, "Ensure create node with value");
	cr_expect_eq(result, EXIT_SUCCESS, "Ensure return 1 if success");
	free_env_lst(&head_env);
}

Test(env_lst_add_back, add_list_with_node)
{
	t_env	*head_env = NULL;
	int		result;

	env_lst_add_back(&head_env, strdup("SHELL"), strdup("/bin/bash"));
	env_lst_add_back(&head_env, strdup("SHELL"), strdup("/bin/bash"));
	result = env_lst_add_back(&head_env,strdup("SHELL"), strdup("/bin/bash"));
	cr_expect(head_env->name, "Ensure create node with name");
	cr_expect(head_env->value, "Ensure create node with value");
	cr_expect(head_env->next->name,
	"Ensure create node with name and insertion at the end of the list and change pointer to last node");
	cr_expect(head_env->next->value, "Ensure create node with value and insertion at the end of the list and change pointer to last node");
	cr_expect(head_env->next->next->name, "Ensure create node with name and insertion at the end of the list and change pointer to last node");
	cr_expect(head_env->next->next->value, "Ensure create node with value and insertion at the end of the list and change pointer to last node");
	cr_expect_eq(result, EXIT_SUCCESS, "Ensure return 1 if success");
	free_env_lst(&head_env);
}
