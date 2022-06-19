/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 08:02:13 by alida-si          #+#    #+#             */
/*   Updated: 2021/11/10 00:46:17 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_type(const char *str, va_list ap)
{
	int	len;

	len = 0;
	if (*str == 'c' || *str == '%')
		len = convert_char(*str, ap);
	else if (*str == 'i' || *str == 'd')
		len = convert_int(ap);
	else if (*str == 's')
		len = convert_str(ap);
	else if (*str == 'u')
		len = convert_un(ap);
	else if (*str == 'x' || *str == 'X' || *str == 'p')
		len = convert_hex(*str, ap);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		len;

	va_start(ap, str);
	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			len += check_type(&str[i], ap);
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			len++;
		}
		i++;
	}
	va_end(ap);
	return (len);
}
