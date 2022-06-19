/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:31:32 by alida-si          #+#    #+#             */
/*   Updated: 2022/02/23 15:37:51 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrncmp(const char *s1, const char *s2, size_t len)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				i;
	int				j;
	int				count;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	count = 0;
	while (count < len)
	{
		if (str1[i] != str2[j])
		{
			return (0);
		}
		i--;
		j--;
		count++;
	}
	return (1);
}
