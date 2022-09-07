/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 05:24:41 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/07 16:28:54 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*	IS_REDIRECT_REDIRECT
**	------------
**	DESCRIPTION
**	Compare if check value is REDIRECT followed by REDIRECT.
**	PARAMETERS
**	#1. The integer (value);
**	#1. The integer (next_value);
**	RETURN VALUES
**	Return true if it is and false if not
*/
static bool	is_redirect_redirect(int value, int next_value)
{
	if (value != PIPE && value != WORD && next_value != PIPE
		&& next_value != WORD)
		return (true);
	return (false);
}

/*	SYNTAX_REDIRECT_ERROR
**	------------
**	DESCRIPTION
**	Checks the next token value and put the syntax error message.
**	PARAMETERS
**	#1. The pointer to data struct (data);
**	#2. The token value (next_value);
**	RETURN VALUES
**	Return 0 if successful and 1 if not
*/
static int	syntax_redirect_error(int next_value)
{
	if (next_value == INPUT)
		return (syntax_error(SYNTAX_ERR_INPUT));
	if (next_value == HEREDOC)
		return (syntax_error(SYNTAX_ERR_HEREDOC));
	if (next_value == TRUNC)
		return (syntax_error(SYNTAX_ERR_TRUNC));
	if (next_value == APPEND)
		return (syntax_error(SYNTAX_ERR_APPEND));
	return (0);
}

/*	PARSER
**	------------
**	DESCRIPTION
**	Checks the order of tokens to ensure it is grammatical.
**	PARAMETERS
**	#1. The pointer to data struct (data);
**	RETURN VALUES
**	Return 0 if successful and 1 if not
*/
int	parser(void)
{
	t_token	*temp;

	if (g_data.head_token == NULL)
		return (0);
	temp = g_data.head_token;
	if (temp->value == PIPE)
		return (syntax_error(SYNTAX_ERR_PIPE));
	while (temp->next != NULL)
	{
		if (is_pipe_pipe(temp->value, temp->next->value))
			return (syntax_error(SYNTAX_ERR_PIPE));
		else if (is_redirect_pipe(temp->value, temp->next->value))
			return (syntax_error(SYNTAX_ERR_PIPE));
		else if (is_redirect_redirect(temp->value, temp->next->value))
			return (syntax_redirect_error(temp->next->value));
		temp = temp->next;
	}
	if (temp->value == PIPE)
		return (syntax_error(SYNTAX_ERR_PIPE));
	else if (temp->value != WORD)
		return (syntax_error(SYNTAX_ERR_NEWLINE));
	return (0);
}
