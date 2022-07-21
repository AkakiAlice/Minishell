#include <criterion/criterion.h>
#include "minishell.h"

Test(parser, only_pipe)
{
	t_token	*last_token = NULL;
	int	result;

	token_lst_add_back(&last_token, PIPE);
	result = parser(last_token);
	cr_expect_eq(result, 1, "Ensure return 1 if you only have one pipe");
	free_token_lst(&last_token);
}

Test(parser, pipe_pipe)
{
	t_token	*last_token = NULL;
	int	result;

	token_lst_add_back(&last_token, WORD);
	token_lst_add_back(&last_token, PIPE);
	token_lst_add_back(&last_token, PIPE);
	token_lst_add_back(&last_token, WORD);
	result = parser(last_token);
	cr_expect_eq(result, 1, "Ensure return 1 if after pipe there is pipe");
	free_token_lst(&last_token);
}
