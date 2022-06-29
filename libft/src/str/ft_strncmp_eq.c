/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_eq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 08:03:31 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/06/29 08:04:04 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	FT_STRNCMP_EQ
**	------------
**	DESCRIPTION
**	Compares s1 and s2 not more than n characters.
**	PARAMETERS
**	#1. The string (s1);
**	#2. The string (s2);
**	#3. The amount of character will be compared (n);
**	RETURN VALUES
**	Return 1 if strings are equal and 0 if it's different.
*/
int	ft_strncmp_eq(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (*(s1 + i) || *(s2 + i)))
	{
		if (*(s1 + i) != *(s2 + i))
			return (0);
		i++;
	}
	return (1);
}
