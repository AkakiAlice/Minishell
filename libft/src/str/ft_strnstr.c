/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 12:57:40 by alida-si          #+#    #+#             */
/*   Updated: 2021/08/02 14:56:39 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ind1;
	size_t	ind2;

	ind1 = 0;
	ind2 = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (ind1 < len && haystack[ind1])
	{
		while (haystack[ind1 + ind2] == needle[ind2]
			&& (ind1 + ind2) < len && needle[ind2])
			ind2++;
		if (needle[ind2] == '\0')
			return ((char *)haystack + ind1);
		ind1++;
		ind2 = 0;
	}
	return (NULL);
}
