/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_withou_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 13:09:01 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/08 07:59:00 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	COUNT_QUOTES_CLOSED
**	------------
**	DESCRIPTION
**	Count quotes closed.
**	PARAMETERS
**	#1. The variable value (var_value);
**	RETURN VALUES
**	Return count quotes.
*/
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

/*	STRLEN_WITHOUT_QUOTES
**	------------
**	DESCRIPTION
**	Get string length without quotes.
**	PARAMETERS
**	#1. The variable value (var_value);
**	RETURN VALUES
**	Return string length.
*/
int	strlen_without_quotes(char *var_value)
{
	return (ft_strlen(var_value) - count_quotes_closed(var_value) + 1);
}

/*	IS_SAVE_CHAR
**	------------
**	DESCRIPTION
**	Check if the char can be saved.
**	PARAMETERS
**	#1. The pointers to quote struct (quote);
**	#2. The character (ch);
**	RETURN VALUES
**	Return string length.
*/
bool	is_save_char(t_quotes *quote, char ch)
{
	bool	is_save;

	is_save = false;
	if (!quote->in)
	{
		quote->type = is_quote_type(ch);
		if (quote->type != -1)
			quote->in = true;
		else
			is_save = true;
	}
	else if (ch == quote->type)
		quote->in = false;
	else
		is_save = true;
	return (is_save);
}

/*	STR_WITHOUT_QUOTES
**	------------
**	DESCRIPTION
**	Save string without quotes.
**	PARAMETERS
**	#1. The string (str);
**	RETURN VALUES
**	Return allocated memory.
*/
char	*str_without_quotes(char *str)
{
	t_quotes	quote;
	char		*result;
	int			i;

	result = (char *)malloc(sizeof(char) * (strlen_without_quotes(str)));
	if (!result)
		return (NULL);
	quote.in = false;
	i = 0;
	while (*str)
	{
		if (is_save_char(&quote, *str))
			result[i++] = *str;
		str++;
	}
	result[i] = '\0';
	return (result);
}
