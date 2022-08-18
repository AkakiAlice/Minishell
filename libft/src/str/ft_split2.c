/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 23:26:26 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/18 05:57:17 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	token_count(char const *s, char c)
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
			if (s[i] == '\'')
				skip(s, i, '\'');
			else if (s[i] == '\"')
				skip(s, i, '\"');
			nb++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (nb);
}

char const	*quote_alloc(char const *s, char **matrix, char c, char quote)
{
	int	len_ptr;

	len_ptr = 0;
	while (s[len_ptr + 1] != quote)
		len_ptr++;
	*matrix = ft_substr(s, 0, (len_ptr + 2));
	s = s + len_ptr;
	s++;
	s++;
	while (*s == c)
		s++;
	return (s);
}

int	is_not_quote(const char *s, char c, int i, char **matrix)
{
	int	len_ptr;

	len_ptr = 0;
	while (s[len_ptr] != c && s[len_ptr])
		len_ptr++;
	matrix[i] = ft_substr(s, 0, len_ptr);
	if (matrix[i] == NULL)
		ft_matrix_free(&matrix);
	return (len_ptr);
}

void	letter_alloc(char **matrix, char const *s, char c, size_t nb_token)
{
	size_t	len_ptr;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < nb_token)
	{
		if (*s == c)
		{
			while (*++s == c)
				;
		}
		if (*s != c && *s != '\'' && *s != '\"')
		{
			len_ptr = is_not_quote(s, c, i, matrix);
			s = s + len_ptr;
		}
		if (*s == '\'')
			s = quote_alloc(s, &matrix[i], c, '\'');
		else if (*s == '\"')
			s = quote_alloc(s, &matrix[i], c, '\"');
		i++;
	}
	matrix[i] = NULL;
}

char	**ft_split2(char const *s, char c)
{
	char	**matrix;
	size_t	nb_token;

	if (!s)
		return (NULL);
	nb_token = token_count(s, c);
	matrix = (char **)malloc(((sizeof(char *)) * (nb_token + 1)));
	if (!matrix)
		return (NULL);
	letter_alloc(matrix, s, c, nb_token);
	return (matrix);
}
