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

Test(parser, pipe_word)
{
	t_token	*last_token = NULL;
	int	result;

	token_lst_add_back(&last_token, WORD);
	token_lst_add_back(&last_token, PIPE);
	token_lst_add_back(&last_token, WORD);
	token_lst_add_back(&last_token, PIPE);
	token_lst_add_back(&last_token, WORD);
	result = parser(last_token);
	cr_expect_eq(result, 0, "Ensure return 0 if after pipe there is word");
	free_token_lst(&last_token);
}

Test(parser, pipe_redirect)
{
	t_token	*last_token = NULL;
	int	result;

	token_lst_add_back(&last_token, WORD);
	token_lst_add_back(&last_token, PIPE);
	token_lst_add_back(&last_token, WORD);
	token_lst_add_back(&last_token, TRUNC);
	token_lst_add_back(&last_token, WORD);
	result = parser(last_token);
	cr_expect_eq(result, 0, "Ensure return 0 if after pipe there is redirect");
	free_token_lst(&last_token);
}

Test(parser, pipe_empty)
{
	t_token	*last_token = NULL;
	int	result;

	token_lst_add_back(&last_token, WORD);
	token_lst_add_back(&last_token, PIPE);
	token_lst_add_back(&last_token, WORD);
	token_lst_add_back(&last_token, PIPE);
	result = parser(last_token);
	cr_expect_eq(result, 1, "Ensure return 1 if after pipe there is nothing");
	free_token_lst(&last_token);
}

Test(parser, redirect_pipe)
{
	t_token	*last_token = NULL;
	int	result;

	token_lst_add_back(&last_token, INPUT);
	token_lst_add_back(&last_token, PIPE);
	token_lst_add_back(&last_token, WORD);
	result = parser(last_token);
	cr_expect_eq(result, 1, "Ensure return 1 if after redirect there is pipe");
	free_token_lst(&last_token);
}

Test(parser, redirect_empty)
{
	t_token	*last_token = NULL;
	int	result;

	token_lst_add_back(&last_token, APPEND);
	result = parser(last_token);
	cr_expect_eq(result, 1, "Ensure return 1 if after redirect there is nothing");
	free_token_lst(&last_token);
}
