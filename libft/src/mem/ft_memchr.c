/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:22:32 by alida-si          #+#    #+#             */
/*   Updated: 2021/08/17 11:17:12 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	*str;

	str = (unsigned char *)s;
	c = (unsigned char)c;
	index = 0;
	while (index < n)
	{
		if (str[index] == c)
			return ((void *)str + index);
		index++;
	}
	return (NULL);
}
