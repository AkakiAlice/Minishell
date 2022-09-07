/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 05:33:53 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/07 18:59:39 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	IS_QUOTE_TYPE
**	------------
**	DESCRIPTION
**	Check character is simple quote or double quote.
**	PARAMETERS
**	#1. The character (ch);
**	RETURN VALUES
**	Return 39 if the char is in single quotes, 34 for double quotes
**	and -1 if dont have quotes.
*/
int	is_quote_type(char ch)
{
	if (ch == S_QUOTE)
		return (S_QUOTE);
	if (ch == D_QUOTE)
		return (D_QUOTE);
	return (-1);
}

/*	VALIDATE_QUOTE_CLOSED
**	------------
**	DESCRIPTION
**	Check for unclosed quotes.
**	PARAMETERS
**	#1. The pointers to variable value (var_value);
**	RETURN VALUES
**	Return true if the quotes are closed and false if aren't not.
*/
bool	validate_quote_closed(void)
{
	int		quote_type;
	bool	quote_closed;
	char	*cmd_line;

	quote_closed = true;
	cmd_line = g_data.cmd_line;
	while (*cmd_line)
	{
		if (quote_closed)
		{
			quote_type = is_quote_type(*cmd_line);
			if (quote_type != -1)
				quote_closed = false;
		}
		else if (*cmd_line == quote_type)
			quote_closed = true;
		cmd_line++;
	}
	return (quote_closed);
}

/*	VALIDATE_QUOTE_SPACE
**	------------
**	DESCRIPTION
**	Check for spaces outside quotes.
**	PARAMETERS
**	#1. The pointers to variable value (var_value);
**	RETURN VALUES
**	Return true if there is no space and false if it there is.
*/
bool	validate_quote_space(char *var_value)
{
	int		quote_type;
	bool	quote_closed;

	quote_closed = true;
	while (*var_value)
	{
		if (*var_value == ' ' && quote_closed)
			return (false);
		if (quote_closed)
		{
			quote_type = is_quote_type(*var_value);
			if (quote_type != -1)
				quote_closed = false;
		}
		else if (*var_value == quote_type)
			quote_closed = true;
		var_value++;
	}
	return (true);
}
