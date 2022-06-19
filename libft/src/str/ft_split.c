/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:42:24 by alida-si          #+#    #+#             */
/*   Updated: 2021/08/12 11:42:24 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	token_count(char const *s, char c)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			nb++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (nb);
}

static char	**free_matrix(char **matrix, size_t i)
{
	while ((int)i >= 0)
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i--;
	}
	free(matrix);
	matrix = NULL;
	return (matrix);
}

static void	letter_aloc(char **matrix, char const *s, char c, size_t nb_token)
{
	size_t	len_ptr;
	size_t	i;

	i = 0;
	while (i < nb_token)
	{
		if (*s == c)
			s++;
		else if (*s != c)
		{
			len_ptr = 0;
			while (s[len_ptr] != c && s[len_ptr])
				len_ptr++;
			matrix[i] = ft_substr(s, 0, len_ptr);
			if (matrix[i] == NULL)
				free_matrix(matrix, i);
			s = s + len_ptr;
			i++;
		}
	}
	matrix[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	size_t	nb_token;

	if (!s)
		return (NULL);
	nb_token = token_count(s, c);
	matrix = (char **)malloc(((sizeof(char *)) * (nb_token + 1)));
	if (!matrix)
		return (NULL);
	letter_aloc(matrix, s, c, nb_token);
	return (matrix);
}
