/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 21:45:50 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/26 22:32:13 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	IS_DOUBLE_SINGLE_QUOTES
**	------------
**	DESCRIPTION
**	Checks if single quotes are duplicated.
**	PARAMETERS
**	#1. The name of the variable to expand (str);
**	RETURN VALUES
**	Returns 1 if duplicated, otherwise returns 0
*/
int	is_double_single_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\'')
	{
		i++;
	}
	if (i % 2 == 0)
		return (1);
	return (0);
}

/*	DONT_EXPAND
**	------------
**	DESCRIPTION
**	Checks if it is a valid string .
**	PARAMETERS
**	#1. The name of the variable to expand (str);
**	RETURN VALUES
**	Returns 1 if invalid string, otherwise returns 0
*/
int	dont_expand(char *str)
{
	if (ft_strlen(str) == 1 || str[1] == '$')
		return (1);
	return (0);
}

/*	CLEAN_QUOTES
**	------------
**	DESCRIPTION
**	Separates and removes quotes from the name of the variable to be expanded.
**	PARAMETERS
**	#1. The name of the variable to expand (str);
**	#2. The type of quote to be removed (quote);
**	RETURN VALUES
**	-
*/
void	clean_quotes(char **str, char quote)
{
	char	**aux;

	aux = ft_split(*str, quote);
	free(*str);
	*str = ft_strdup(aux[0]);
	ft_matrix_free(&aux);
}
