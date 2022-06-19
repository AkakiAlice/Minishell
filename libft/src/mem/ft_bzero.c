/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:20:31 by alida-si          #+#    #+#             */
/*   Updated: 2021/07/30 19:21:10 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	int				index;
	unsigned char	*dest;

	dest = (unsigned char *)str;
	index = 0;
	while (n > 0)
	{
		dest[index] = 0;
		index++;
		n--;
	}
}
