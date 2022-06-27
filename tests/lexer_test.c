#include <criterion/criterion.h>
#include "minishell.h"

// TODO: create simple test ensure validate only pipe
// TODO: create test pipe entry as string
// TODO: create test add back token lst

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
