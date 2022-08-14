#include <criterion/criterion.h>
#include "minishell.h"

static int	count_nodes(t_token *head_token)
{
	t_token	*current;
	int	result;

	if (head_token == NULL)
		return (0);
	current = head_token->next;
	result = 0;
	while (current != head_token)
	{
		result++;
		current = current->next;
	}
	result++;
	return (result);
}

Test(lexer, is_pipe)
{
	char	**cmd;
	t_token	*head_token = NULL;
	int		count_token_nodes = 0;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup("|");
	cmd[1] = NULL;
	lexer(&head_token, cmd);
	count_token_nodes = count_nodes(head_token);
	cr_expect_eq(head_token->value, PIPE, "Ensure return 124 if PIPE");
	cr_expect_eq(count_token_nodes, 1, "Ensure save 1 node in token list");
	free_token_lst(&head_token);
	ft_matrix_free(cmd);
}

Test(lexer, pipe_with_simple_quote)
{
	char	**cmd;
	t_token	*head_token = NULL;
	int		count_token_nodes = 0;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup("'|'");
	cmd[1] = NULL;
	lexer(&head_token, cmd);
	count_token_nodes = count_nodes(head_token);
	cr_expect_neq(head_token->value, PIPE,
		"Ensure return not 0 if there are other characters");
	cr_expect_eq(count_token_nodes, 1, "Ensure save 1 node in token list");
	free_token_lst(&head_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_input)
{
	char	**cmd;
	t_token	*head_token = NULL;
	int		count_token_nodes = 0;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup("<");
	cmd[1] = NULL;
	lexer(&head_token, cmd);
	count_token_nodes = count_nodes(head_token);
	cr_expect_eq(head_token->value, INPUT, "Ensure return 1 if INPUT");
	cr_expect_eq(count_token_nodes, 1, "Ensure save 1 node in token list");
	free_token_lst(&head_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_not_input)
{
	char	**cmd;
	t_token	*head_token = NULL;
	int		count_token_nodes = 0;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup("   < ");
	cmd[1] = NULL;
	lexer(&head_token, cmd);
	count_token_nodes = count_nodes(head_token);
	cr_expect_neq(head_token->value, INPUT,
		"Ensure return not 1 if there are other characters");
	cr_expect_eq(count_token_nodes, 1, "Ensure save 1 node in token list");
	free_token_lst(&head_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_heredoc)
{
	char	**cmd;
	t_token	*head_token = NULL;
	int		count_token_nodes = 0;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup("<<");
	cmd[1] = NULL;
	lexer(&head_token, cmd);
	count_token_nodes = count_nodes(head_token);
	cr_expect_eq(head_token->value, HEREDOC, "Ensure return 2 if HEREDOC");
	cr_expect_eq(count_token_nodes, 1, "Ensure save 1 node in token list");
	free_token_lst(&head_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_not_heredoc)
{
	char	**cmd;
	t_token	*head_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup("< <");
	cmd[1] = NULL;
	lexer(&head_token, cmd);
	cr_expect_neq(head_token->value, HEREDOC,
		"Ensure return not 2 if there are other characters");
	free_token_lst(&head_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_trunc)
{
	char	**cmd;
	t_token	*head_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup(">");
	cmd[1] = NULL;
	lexer(&head_token, cmd);
	cr_expect_eq(head_token->value, TRUNC, "Ensure return 3 if TRUNC");
	free_token_lst(&head_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_not_trunc)
{
	char	**cmd;
	t_token	*head_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup(" >");
	cmd[1] = NULL;
	lexer(&head_token, cmd);
	cr_expect_neq(head_token->value, TRUNC,
		"Ensure return not 3 if there are other characters");
	free_token_lst(&head_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_append)
{
	char	**cmd;
	t_token	*head_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup(">>");
	cmd[1] = NULL;
	lexer(&head_token, cmd);
	cr_expect_eq(head_token->value, APPEND, "Ensure return 4 if APPEND");
	free_token_lst(&head_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_not_append)
{
	char	**cmd;
	t_token	*head_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup("> >");
	cmd[1] = NULL;
	lexer(&head_token, cmd);
	cr_expect_neq(head_token->value, APPEND,
		"Ensure return not 4 if there are other characters");
	free_token_lst(&head_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_word_2_char)
{
	char	**cmd;
	t_token	*head_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup(" >");
	cmd[1] = NULL;
	lexer(&head_token, cmd);
	cr_expect_eq(head_token->value, WORD, "Ensure return 5 if WORD");
	free_token_lst(&head_token);
	ft_matrix_free(cmd);
}

Test(lexer, is_word_more_2_char)
{
	char	**cmd;
	t_token	*head_token = NULL;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = strdup(" OK ");
	cmd[1] = NULL;
	lexer(&head_token, cmd);
	cr_expect_eq(head_token->value, WORD, "Ensure return 5 if WORD");
	free_token_lst(&head_token);
	ft_matrix_free(cmd);
}
