/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 05:33:53 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/14 06:57:20 by pmitsuko         ###   ########.fr       */
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
static int	is_quote_type(char ch)
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
**	Return 0 if the quotes are closed and 1 if aren't not.
*/
bool	validate_quote_closed(char *var_value)
{
	int		quote_type;
	bool	quote_closed;

	quote_closed = true;
	while (*var_value)
	{
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

int	count_quotes_closed(char *var_value)
{
	int		quote_type;
	bool	quote_closed;
	int		count_quotes;

	quote_closed = true;
	count_quotes = 0;
	while (*var_value)
	{
		if (quote_closed)
		{
			quote_type = is_quote_type(*var_value);
			if (quote_type != -1)
			{
				quote_closed = false;
				count_quotes++;
			}
		}
		else if (*var_value == quote_type)
			quote_closed = true;
		var_value++;
	}
	return (count_quotes * 2);
}

char	*str_without_quotes(char *str)
{
	int		quote_type;
	bool	quote_closed;
	char	*result;
	int		len;
	int		i;

	len = ft_strlen(str) - count_quotes_closed(str) + 1;
	result = (char *)malloc(sizeof(char *) * (len));
	if (!result)
		return (NULL);
	quote_closed = true;
	i = 0;
	while (*str)
	{
		if (quote_closed)
		{
			quote_type = is_quote_type(*str);
			if (quote_type != -1)
				quote_closed = false;
			else
				result[i++] = *str;
		}
		else if (*str == quote_type)
			quote_closed = true;
		else
			result[i++] = *str;
		str++;
	}
	result[i] = '\0';
	return (result);
}
