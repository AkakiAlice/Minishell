/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 05:59:10 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/04 08:00:20 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reserved_char(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '<')
		return (INPUT);
	if (c == '>')
		return (TRUNC);
	if (c == ' ')
		return (SPC);
	if (c == S_QUOTE)
		return (S_QUOTE);
	if (c == D_QUOTE)
		return (D_QUOTE);
	return (WORD);
}

static int	count_words_cmd(char *cmd)
{
	int		word_count;
	int		type_char;
	bool	is_word;

	word_count = 0;
	is_word = false;
	while (*cmd)
	{
		type_char = reserved_char(*cmd);
		if (type_char != WORD)
		{
			if (is_word)
				word_count++;
			if (type_char == S_QUOTE)
			{
				cmd++;
				while (*cmd && *cmd != S_QUOTE)
					cmd++;
			}
			if (type_char == D_QUOTE)
			{
				cmd++;
				while (*cmd && *cmd != D_QUOTE)
					cmd++;
			}
			if (ft_strncmp_eq(cmd, "<<", 2))
				cmd++;
			if (ft_strncmp_eq(cmd, ">>", 2))
				cmd++;
			if (type_char != SPC)
				word_count++;
			is_word = false;
		}
		else
			is_word = true;
		if (*cmd)
			cmd++;
	}
	if (is_word)
		word_count++;
	return (word_count);
}

char	*strchr_reserved(char *cmd)
{
	while (*cmd != '\0')
	{
		if (reserved_char(*cmd) != WORD)
			return (cmd);
		cmd++;
	}
	return (NULL);
}

void	make_words(char **words, char *cmd, int num_word)
{
	char	*reserved_char;
	int		i;
	int		size;
	int		j;

	i = 0;
	while (i < num_word)
	{
		reserved_char = strchr_reserved(cmd);
		if (reserved_char != NULL)
		{
			size = reserved_char - cmd;
			if (size != 0)
			{
				*words = ft_substr(cmd, 0, size);
				i++;
				words++;
			}
			if (*reserved_char == SPC)
			{
				while (*reserved_char == SPC)
					reserved_char++;
			}
			else if (*reserved_char == S_QUOTE)
			{
				size = 2;
				j = 1;
				while (reserved_char[j] && reserved_char[j] != S_QUOTE)
				{
					size++;
					j++;
				}
				*words = ft_substr(reserved_char, 0, size);
				while (*reserved_char && j > -1)
				{
					reserved_char++;
					j--;
				}
				i++;
				words++;
			}
			else
			{
				if (ft_strncmp_eq(reserved_char, "<<", 2))
				{
					*words = ft_substr(reserved_char, 0, 2);
					reserved_char++;
				}
				else if (ft_strncmp_eq(reserved_char, ">>", 2))
				{
					*words = ft_substr(reserved_char, 0, 2);
					reserved_char++;
				}
				else
					*words = ft_substr(reserved_char, 0, 1);
				i++;
				words++;
				reserved_char++;
			}
			cmd = reserved_char;
		}
		else
		{
			*words = ft_substr(cmd, 0, ft_strlen(cmd) + 1);
			i++;
			words++;
		}
	}
	*words = NULL;
}

char	**split_cmd(char *cmd)
{
	char	**words;
	int		num_word;

	if (!cmd)
		return (NULL);
	num_word = count_words_cmd(cmd);
	words = (char **)malloc(((sizeof(char *)) * (num_word + 1)));
	if (!words)
		return (NULL);
	make_words(words, cmd, num_word);
	return (words);
}

