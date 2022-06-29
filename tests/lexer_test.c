#include <criterion/criterion.h>
#include "minishell.h"

Test(ft_strncmp_eq, is_equal)
{
	char	*s1 = {"|"};
	char	*s2 = {"|"};
	int		result;

	result = ft_strncmp_eq(s1, s2, 1);
	cr_expect_eq(result, 1, "Ensure return 1 if string is equal");
}

Test(lexer, is_pipe)
{
	char	**cmd;
	t_token	*last_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup("|");
	cmd[1] = NULL;
	lexer(&last_token, cmd);
	cr_expect_eq(last_token->value, PIPE, "Ensure return 0 if PIPE");
	free_token_lst(&last_token);
	ft_matrix_free(cmd);
}

Test(lexer, pipe_with_space)
{
	char	**cmd;
	t_token	*last_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup("   | ");
	cmd[1] = NULL;
	lexer(&last_token, cmd);
	cr_expect_neq(last_token->value, PIPE,
		"Ensure return not 0 if there are other characters");
	free_token_lst(&last_token);
	ft_matrix_free(cmd);
}

Test(lexer, pipe_with_simple_quote)
{
	char	**cmd;
	t_token	*last_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup("'|'");
	cmd[1] = NULL;
	lexer(&last_token, cmd);
	cr_expect_neq(last_token->value, PIPE,
		"Ensure return not 0 if there are other characters");
	free_token_lst(&last_token);
	ft_matrix_free(cmd);
}
