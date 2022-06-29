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

Test(lexer, is_input)
{
	char	**cmd;
	t_token	*last_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup("<");
	cmd[1] = NULL;
	lexer(&last_token, cmd);
	cr_expect_eq(last_token->value, INPUT, "Ensure return 1 if INPUT");
	free_token_lst(&last_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_not_input)
{
	char	**cmd;
	t_token	*last_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup("   < ");
	cmd[1] = NULL;
	lexer(&last_token, cmd);
	cr_expect_neq(last_token->value, INPUT,
		"Ensure return not 1 if there are other characters");
	free_token_lst(&last_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_heredoc)
{
	char	**cmd;
	t_token	*last_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup("<<");
	cmd[1] = NULL;
	lexer(&last_token, cmd);
	cr_expect_eq(last_token->value, HEREDOC, "Ensure return 2 if HEREDOC");
	free_token_lst(&last_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_not_heredoc)
{
	char	**cmd;
	t_token	*last_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup("< <");
	cmd[1] = NULL;
	lexer(&last_token, cmd);
	cr_expect_neq(last_token->value, HEREDOC,
		"Ensure return not 2 if there are other characters");
	free_token_lst(&last_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_trunc)
{
	char	**cmd;
	t_token	*last_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup(">");
	cmd[1] = NULL;
	lexer(&last_token, cmd);
	cr_expect_eq(last_token->value, TRUNC, "Ensure return 3 if TRUNC");
	free_token_lst(&last_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_not_trunc)
{
	char	**cmd;
	t_token	*last_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup(" >");
	cmd[1] = NULL;
	lexer(&last_token, cmd);
	cr_expect_neq(last_token->value, TRUNC,
		"Ensure return not 3 if there are other characters");
	free_token_lst(&last_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_append)
{
	char	**cmd;
	t_token	*last_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup(">>");
	cmd[1] = NULL;
	lexer(&last_token, cmd);
	cr_expect_eq(last_token->value, APPEND, "Ensure return 4 if APPEND");
	free_token_lst(&last_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_not_append)
{
	char	**cmd;
	t_token	*last_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup("> >");
	cmd[1] = NULL;
	lexer(&last_token, cmd);
	cr_expect_neq(last_token->value, APPEND,
		"Ensure return not 4 if there are other characters");
	free_token_lst(&last_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_word_2_char)
{
	char	**cmd;
	t_token	*last_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup(" >");
	cmd[1] = NULL;
	lexer(&last_token, cmd);
	cr_expect_eq(last_token->value, WORD, "Ensure return 5 if WORD");
	free_token_lst(&last_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_word_more_2_char)
{
	char	**cmd;
	t_token	*last_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup(" OK ");
	cmd[1] = NULL;
	lexer(&last_token, cmd);
	cr_expect_eq(last_token->value, WORD, "Ensure return 5 if WORD");
	free_token_lst(&last_token);
	ft_matrix_free(cmd);
}
