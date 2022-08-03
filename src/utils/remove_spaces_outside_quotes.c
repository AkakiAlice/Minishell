/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces_outside_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 05:45:50 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/03 05:54:32 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	CHECK_QUOTES_CLOSED
**	------------
**	DESCRIPTION
**	Checks if the quotes were closed. The type of checked to ensure in cases of
**	quotes inside quotes.
**	PARAMETERS
**	#1. The struct quotes (quotes);
**	#1. The character (c);
**	RETURN VALUES
**	-
*/
void	check_quotes_closed(t_quotes *quotes, char c)
{
	if (!quotes->in)
	{
		quotes->type = is_quote_type(c);
		if (quotes->type != -1)
			quotes->in = true;
	}
	else if (c == quotes->type)
		quotes->in = false;
}

/*	STRLEN_WITHOUT_SPACE
**	------------
**	DESCRIPTION
**	Counts characters without considering spaces outside the quotes.
**	PARAMETERS
**	#1. The string (str);
**	RETURN VALUES
**	Return string length without space outside quotes.
*/
static int	strlen_without_space(char *str)
{
	t_quotes	quotes;
	int			str_len;
	int			i;

	i = 0;
	str_len = 0;
	quotes.in = false;
	quotes.type = -1;
	while (str[i])
	{
		if (quotes.in || str[i] != ' ')
			str_len++;
		check_quotes_closed(&quotes, str[i]);
		i++;
	}
	return (str_len);
}

/*	REMOVE_SPACES_OUTSIDE_QUOTE
**	------------
**	DESCRIPTION
**	The space characters that are in the string are removed. Spaces in quotes
**	are preserved.
**	PARAMETERS
**	#1. The string (str);
**	RETURN VALUES
**	Return allocated memory from new string without space.
*/
char	*remove_spaces_outside_quote(char *str)
{
	t_quotes	quotes;
	char		*new_str;
	int			i;

	if (!str)
		return (NULL);
	new_str = malloc(sizeof(char) * strlen_without_space(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	quotes.in = false;
	quotes.type = -1;
	while (*str)
	{
		if (quotes.in || *str != ' ')
			new_str[i++] = *str;
		check_quotes_closed(&quotes, *str);
		str++;
	}
	new_str[i] = '\0';
	return (new_str);
}
