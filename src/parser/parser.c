/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 05:24:41 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/21 06:57:20 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_pipe(int value)
{
	if (value == PIPE)
	{
		put_msg("minishell", SYNTAX_ERR_PIPE, 2);
		return (true);
	}
	return (false);
}

static bool	is_pipe_pipe(int value, int next_value)
{
	if (value == PIPE && next_value == PIPE)
	{
		put_msg("minishell", SYNTAX_ERR_PIPE, 2);
		return (true);
	}
	return (false);
}

static bool	is_redirect_pipe(int value, int next_value)
{
	if (value != PIPE && value != WORD && next_value == PIPE)
	{
		put_msg("minishell", SYNTAX_ERR_PIPE, 2);
		return (true);
	}
	return (false);
}

static int	is_word(int value)
{
	if (value != WORD)
	{
		put_msg("minishell", SYNTAX_ERR_NEWLINE, 2);
		return (false);
	}
	return (true);
}

int	parser(t_token *last_token)
{
	t_token	*current;

	if (last_token == NULL)
		return (0);
	current = last_token->next;
	if (is_pipe(current->value))
		return (1);
	while (current != last_token)
	{
		if (is_pipe_pipe(current->value, current->next->value))
			return (1);
		else if (is_redirect_pipe(current->value, current->next->value))
			return (1);
		current = current->next;
	}
	if (is_pipe(last_token->value))
		return (1);
	else if (!is_word(last_token->value))
		return (1);
	return (0);
}
