/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 21:45:50 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/11 00:59:03 by alida-si         ###   ########.fr       */
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
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\'')
		i++;
	while (str[i] && str[i] == '\'')
	{
		j++;
		i++;
	}
	if (j == 0)
		return (0);
	if (j % 2 == 0)
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
	char	*swap;
	int		i;

	i = 0;
	aux = ft_split(*str, quote);
	free(*str);
	*str = ft_strdup("");
	while (aux[i])
	{
		swap = *str;
		*str = ft_strjoin(swap, aux[i]);
		free(swap);
		i++;
	}
	ft_matrix_free(&aux);
}

/*	ADD_SPACE
**	------------
**	DESCRIPTION
**	Include space after the string.
**	PARAMETERS
**	#1. The result string (result);
**	RETURN VALUES
**	-
*/
void	add_space(char **result)
{
	char	*aux;

	aux = ft_strdup(*result);
	free(*result);
	*result = ft_strcat(aux, " ");
	free(aux);
}

/*	STRCAT_SPACE
**	------------
**	DESCRIPTION
**	Concatenate string and include space after the string.
**	PARAMETERS
**	#1. The result string (result);
**	#2. The string (str);
**	#3. The flag to include space at the end (space);
**	RETURN VALUES
**	-
*/
void	strcat_space(char **result, char *str, bool space)
{
	char	*aux;

	aux = ft_strdup(*result);
	free(*result);
	*result = ft_strcat(aux, str);
	free(aux);
	if (space)
		add_space(result);
}
