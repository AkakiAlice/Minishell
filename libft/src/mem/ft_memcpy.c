/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:29:15 by alida-si          #+#    #+#             */
/*   Updated: 2021/07/30 19:30:28 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			index;
	unsigned char	*s;
	unsigned char	*d;

	if (dest == src)
		return (dest);
	index = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	while (index < n)
	{
		*d = *s;
		d++;
		s++;
		index++;
	}
	return (dest);
}
