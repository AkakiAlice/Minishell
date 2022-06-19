/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 19:08:38 by alida-si          #+#    #+#             */
/*   Updated: 2021/08/04 19:08:58 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*aux;

	aux = malloc(count * size);
	if (!aux)
		return (NULL);
	ft_bzero (aux, count * size);
	return ((void *)aux);
}
