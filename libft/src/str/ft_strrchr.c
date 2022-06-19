/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 15:23:18 by alida-si          #+#    #+#             */
/*   Updated: 2021/08/17 13:10:27 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	char_c;

	i = ft_strlen(s);
	str = (char *)s;
	char_c = (char)c;
	while ((i != 0) && (char_c != str[i]))
		i--;
	if (char_c == str[i])
		return (str + i);
	return (NULL);
}
