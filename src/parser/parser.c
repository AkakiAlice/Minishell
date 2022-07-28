/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 05:24:41 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/27 07:14:47 by pmitsuko         ###   ########.fr       */
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

/*	SYNTAX_ERROR
**	------------
**	DESCRIPTION
**	Output message and set exit code.
**	PARAMETERS
**	#1. The pointer to data struct (data);
**	#2. The output message (msg);
**	RETURN VALUES
**	Return 1
*/
int	syntax_error(t_data *data, char *msg)
{
	put_msg("minishell", msg, 2);
	data->status = 2;
	return (1);
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
int	parser(t_data *data)
{
	t_token	*current;

	if (data->last_token == NULL)
		return (0);
	current = data->last_token->next;
	if (is_pipe(current->value))
		return (syntax_error(data, SYNTAX_ERR_PIPE));
	while (current != data->last_token)
	{
		if (is_pipe_pipe(current->value, current->next->value))
			return (syntax_error(data, SYNTAX_ERR_PIPE));
		else if (is_redirect_pipe(current->value, current->next->value))
			return (syntax_error(data, SYNTAX_ERR_PIPE));
		current = current->next;
	}
	if (is_pipe(data->last_token->value))
		return (syntax_error(data, SYNTAX_ERR_PIPE));
	else if (!is_word(data->last_token->value))
		return (syntax_error(data, SYNTAX_ERR_NEWLINE));
	return (0);
}
