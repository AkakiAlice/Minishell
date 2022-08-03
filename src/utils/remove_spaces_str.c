/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 05:45:50 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/03 05:24:11 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strlen_without_space(char *str)
{
	int		quote_type;
	bool	in_quotes;
	int		str_len;
	int		i;

	i = 0;
	str_len = 0;
	in_quotes = false;
	quote_type = -1;
	while (str[i])
	{
		if (in_quotes || str[i] != ' ')
			str_len++;
		if (!in_quotes)
		{
			quote_type = is_quote_type(str[i]);
			if (quote_type != -1)
				in_quotes = true;
		}
		else if (str[i] == quote_type)
			in_quotes = false;
		i++;
	}
	return (str_len);
}

/*	REMOVE_SPACES_STR
**	------------
**	DESCRIPTIONs
**	The space characters that are in the string are removed.
**	PARAMETERS
**	#1. The string (str);
**	RETURN VALUES
**	Return allocated memory from new string without space.
*/
char	*remove_spaces_str(char *str)
{
	int		quote_type;
	bool	in_quotes;
	char	*new_str;
	int		i;

	if (!str)
		return (NULL);
	new_str = malloc(sizeof(char) * strlen_without_space(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	in_quotes = false;
	quote_type = -1;
	while (*str)
	{
		if (in_quotes || *str != ' ')
			new_str[i++] = *str;
		if (!in_quotes)
		{
			quote_type = is_quote_type(*str);
			if (quote_type != -1)
				in_quotes = true;
		}
		else if (*str == quote_type)
			in_quotes = false;
		str++;
	}
	new_str[i] = '\0';
	return (new_str);
}
