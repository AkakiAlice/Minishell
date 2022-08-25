/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp_eq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 08:41:58 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/24 08:42:17 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	STRCMP_EQ
**	------------
**	DESCRIPTION
**	Checks if the strings are the same character and length.
**	PARAMETERS
**	#1. The string (s1);
**	#2. The string (s2);
**	RETURN VALUES
**	Return 1 if strings are equal and 0 if it's different.
*/
int	strcmp_eq(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (*(s1 + i) || *(s2 + i))
	{
		if (*(s1 + i) != *(s2 + i))
			return (0);
		i++;
	}
	return (1);
}
