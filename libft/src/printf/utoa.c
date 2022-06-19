/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 08:26:38 by alida-si          #+#    #+#             */
/*   Updated: 2021/11/09 23:21:24 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*n_convert(char *str, size_t size, unsigned int num)
{
	str[size] = '\0';
	while (size--)
	{
		str[size] = (num % 10) + 48;
		num /= 10;
	}
	return (str);
}

static size_t	nb_size(unsigned int num)
{
	size_t	len;

	len = 1;
	num /= 10;
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}

int	utoa(unsigned int n)
{
	size_t			n_digits;
	char			*str;

	n_digits = nb_size(n);
	str = malloc(sizeof(char) * (n_digits + 1));
	if (str == NULL)
		return (0);
	ft_putstr_fd(n_convert(str, n_digits, n), 1);
	free (str);
	return (n_digits);
}
