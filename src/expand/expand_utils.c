/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 21:45:50 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/26 21:47:19 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	dont_expand(char *str)
{
	if (ft_strlen(str) == 1 || str[1] == '$')
		return (1);
	return (0);
}

void	clean_quotes(char **str, char quote)
{
	char	**aux;

	aux = ft_split(*str, quote);
	free(*str);
	*str = ft_strdup(aux[0]);
	ft_matrix_free(&aux);
}
