/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:12:09 by alida-si          #+#    #+#             */
/*   Updated: 2022/03/29 18:13:54 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, char *s2)
{
	size_t	i;
	size_t	len;
	char	*result;

	len = (ft_strlen(s1) + ft_strlen(s2));
	result = (char *)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (*s1 + 1)
	{
		result[i] = *s1;
		if (!*s1)
		{
			while (*s2)
			{
				result[i] = *s2;
				s2++;
				i++;
			}
		}
		s1++;
		i++;
	}
	result[i] = '\0';
	return (result);
}
