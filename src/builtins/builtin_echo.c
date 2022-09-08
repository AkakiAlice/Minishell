/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 17:48:45 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/08 13:14:50 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	BUILTIN_ECHO
**	------------
**	DESCRIPTION
**	Displays the arguments passed to standard output..
**	PARAMETERS
**	#1. The content to be displayed (word);
**	RETURN VALUES
**	-
*/
void	builtin_echo(char **word)
{
	int	i;

	i = 1;
	while (strcmp_eq(word[i], "-n"))
		i++;
	while (word[i] != NULL)
	{
		ft_printf("%s", word[i]);
		if (word[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (!strcmp_eq(word[1], "-n"))
		ft_printf("\n");
}
