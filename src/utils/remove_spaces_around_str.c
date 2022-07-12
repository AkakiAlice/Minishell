/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces_around_str.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 05:03:11 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/12 06:02:27 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	REMOVE_SPACES_AROUND_STR
**	------------
**	DESCRIPTION
**	The space characters that are at the beginning and end of the string are
**	removed.
**	PARAMETERS
**	#1. The string (str);
**	RETURN VALUES
**	Return allocated memory from new string
*/
char	*remove_spaces_around_str(char *str)
{
	char	*new_str;
	int		str_len;

	if (!str)
		return (NULL);
	while (*str == ' ')
		str++;
	str_len = ft_strlen(str) - 1;
	while (str[str_len] == ' ')
		str_len--;
	new_str = ft_substr(str, 0, str_len + 1);
	return (new_str);
}
