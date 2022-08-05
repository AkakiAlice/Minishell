/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 05:59:10 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/05 05:26:12 by pmitsuko         ###   ########.fr       */
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
	return (WORD);
}

int	is_quote(char c)
{
	if (c == S_QUOTE)
		return (S_QUOTE);
	if (c == D_QUOTE)
		return (D_QUOTE);
	return (-1);
}

static int	count_words_cmd(char *cmd)
{
	int		word_count;
	int		type_char;
	int		quote_type;
	bool	is_word;

	word_count = 0;
	is_word = false;
	while (*cmd)
	{
		type_char = reserved_char(*cmd);
		quote_type = is_quote(*cmd);
		if (quote_type != -1)
		{
			if (quote_type == S_QUOTE)
			{
				cmd++;
				while (*cmd && *cmd != S_QUOTE)
					cmd++;
			}
			else if (quote_type == D_QUOTE)
			{
				cmd++;
				while (*cmd && *cmd != D_QUOTE)
					cmd++;
			}
			is_word = true;
		}
		else if (type_char != WORD)
		{
			if (is_word)
				word_count++;
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

// char	*strchr_quote(char *cmd)
// {
// 	while (*cmd != '\0')
// 	{
// 		if (is_quote(*cmd) != -1)
// 			return (is_quote);
// 		cmd++;
// 	}
// 	return (NULL);
// }

int	find_type_char(char *cmd)
{
	int	quote_type;
	int	char_type;

	while (*cmd != '\0')
	{
		quote_type = is_quote(*cmd);
		char_type = reserved_char(*cmd);
		if (is_quote(*cmd) != -1)
			return (quote_type);
		if (reserved_char(*cmd) != WORD)
			return (char_type);
		cmd++;
	}
	return (-1);
}

void	make_words(char **words, char *cmd, int num_word)
{
	char	*reserve_char;
	int		i;
	int		size;
	int		j;
	int		first_type_char;
	t_quotes	quotes;
	// bool	stop;
	// int		quote_type;
	// int		count_quotes;

	i = 0;
	while (i < num_word)
	{
		// * Identificar se a primeira ocorrencia é aspas
		// * Se for precisa salvar até que tenha a ocorrencia de outro caractere reservado fora das aspas
		first_type_char = find_type_char(cmd);
		if (first_type_char == S_QUOTE || first_type_char == D_QUOTE)
		{
			quotes.in = false;
			j = 0;
			// stop = false;
			while (cmd[j])
			{
				if (!quotes.in)
				{
					if (reserved_char(cmd[j]) != WORD)
						break;
					quotes.type = is_quote_type(cmd[j]);
					if (quotes.type != -1)
						quotes.in = true;
				}
				else if (cmd[j] == quotes.type)
					quotes.in = false;
				// if (!stop)
				j++;
			}
			// ft_printf("size: [%d]\n", j);
			*words = ft_substr(cmd, 0, j);
			i++;
			words++;
			while (*cmd && j > 0)
			{
				cmd++;
				j--;
			}
			// ft_printf("cmd: [%s]\n", cmd);
			// quote_type = strchr_quote(cmd);
			// if (quote_type != -1)
			// {
			// 	size = 0;
			// 	j = 0;
			// 	count_quotes = 2;
			// 	while (reserved_char[j] && count_quotes > -1)
			// 	{
			// 		if (reserved_char[j] == )
			// 		size++;
			// 		j++;
			// 	}
			// 	*words = ft_substr(reserved_char, 0, size);
			// 	while (*reserved_char && j > -1)
			// 	{
			// 		reserved_char++;
			// 		j--;
			// 	}
			// 	i++;
			// 	words++;
			// }
		}
		else if (first_type_char != -1)
		{
			reserve_char = strchr_reserved(cmd);
			if (reserve_char != NULL)
			{
				size = reserve_char - cmd;
				if (size != 0)
				{
					*words = ft_substr(cmd, 0, size);
					i++;
					words++;
				}
				if (*reserve_char == SPC)
				{
					while (*reserve_char == SPC)
						reserve_char++;
				}
				else
				{
					if (ft_strncmp_eq(reserve_char, "<<", 2))
					{
						*words = ft_substr(reserve_char, 0, 2);
						reserve_char++;
					}
					else if (ft_strncmp_eq(reserve_char, ">>", 2))
					{
						*words = ft_substr(reserve_char, 0, 2);
						reserve_char++;
					}
					else
						*words = ft_substr(reserve_char, 0, 1);
					i++;
					words++;
					reserve_char++;
				}
				cmd = reserve_char;
			}
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
	// ft_printf("[%d]\n", num_word);
	words = (char **)malloc(((sizeof(char *)) * (num_word + 1)));
	if (!words)
		return (NULL);
	make_words(words, cmd, num_word);
	return (words);
}

