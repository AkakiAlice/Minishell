/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 05:24:41 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/26 13:28:08 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	IS_PIPE
**	------------
**	DESCRIPTION
**	Compare if check value is PIPE.
**	PARAMETERS
**	#1. The integer (value);
**	RETURN VALUES
**	Return true if PIPE and false if not
*/
static bool	is_pipe(int value)
{
	if (value == PIPE)
		return (true);
	return (false);
}

/*	IS_PIPE_PIPE
**	------------
**	DESCRIPTION
**	Compare if check value is PIPE followed by PIPE.
**	PARAMETERS
**	#1. The integer (value);
**	#1. The integer (next_value);
**	RETURN VALUES
**	Return true if it is and false if not
*/
static bool	is_pipe_pipe(int value, int next_value)
{
	if (value == PIPE && next_value == PIPE)
		return (true);
	return (false);
}

/*	IS_REDIRECT_PIPE
**	------------
**	DESCRIPTION
**	Compare if check value is REDIRECT followed by PIPE.
**	PARAMETERS
**	#1. The integer (value);
**	#1. The integer (next_value);
**	RETURN VALUES
**	Return true if it is and false if not
*/
static bool	is_redirect_pipe(int value, int next_value)
{
	if (value != PIPE && value != WORD && next_value == PIPE)
		return (true);
	return (false);
}

/*	IS_WORD
**	------------
**	DESCRIPTION
**	Compare if check value is WORD.
**	PARAMETERS
**	#1. The integer (value);
**	RETURN VALUES
**	Return true if WORD and false if not
*/
static bool	is_word(int value)
{
	if (value == WORD)
		return (true);
	return (false);
}

/*	PARSER
**	------------
**	DESCRIPTION
**	Checks the order of tokens to ensure it is grammatical.
**	PARAMETERS
**	#1. The pointer to list (last_token);
**	RETURN VALUES
**	Return 0 if successful and 1 if not
*/
int	parser(t_token *last_token)
{
	t_token	*current;

	if (last_token == NULL)
		return (0);
	current = last_token->next;
	if (is_pipe(current->value))
		return (put_msg("minishell", SYNTAX_ERR_PIPE, 2, 1));
	while (current != last_token)
	{
		if (is_pipe_pipe(current->value, current->next->value))
			return (put_msg("minishell", SYNTAX_ERR_PIPE, 2, 1));
		else if (is_redirect_pipe(current->value, current->next->value))
			return (put_msg("minishell", SYNTAX_ERR_PIPE, 2, 1));
		current = current->next;
	}
	if (is_pipe(last_token->value))
		return (put_msg("minishell", SYNTAX_ERR_PIPE, 2, 1));
	else if (!is_word(last_token->value))
		return (put_msg("minishell", SYNTAX_ERR_NEWLINE, 2, 1));
	return (0);
}
