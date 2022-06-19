/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:13:41 by alida-si          #+#    #+#             */
/*   Updated: 2022/06/19 08:51:43 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	convert_char(const char str, va_list ap)
{
	int		n;
	char	c;

	n = 0;
	if (str == 'c')
	{
		c = va_arg(ap, int);
		ft_putchar_fd(c, 1);
		n++;
	}
	if (str == '%')
	{
		c = '%';
		ft_putchar_fd(c, 1);
		n++;
	}
	return (n);
}

int	convert_int(va_list ap)
{
	int		n;
	char	*str;

	str = ft_itoa(va_arg(ap, int));
	n = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (n);
}

int	convert_hex(const char str, va_list ap)
{
	int	n;

	n = 0;
	if (str == 'p')
	{
		ft_putstr_fd("0x", 1);
		n += 2;
		n += itohex(va_arg(ap, unsigned long int), str);
	}
	if (str == 'X' || str == 'x')
		n += itohex(va_arg(ap, unsigned int), str);
	return (n);
}

int	convert_un(va_list ap)
{
	int	n;

	n = utoa(va_arg(ap, int));
	return (n);
}

int	convert_str(va_list ap)
{
	int		n;
	char	*str;

	str = va_arg (ap, char *);
	if (!str)
	{
		write (1, "(null)", 6);
		return (6);
	}
	n = ft_strlen(str);
	ft_putstr_fd(str, 1);
	return (n);
}
