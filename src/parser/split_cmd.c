/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 05:59:10 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/09 06:30:07 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	MAKE_WORDS
**	------------
**	DESCRIPTION
**	Save the words divided by space, pipe and redirectors. If the words is in
**	quotes it is saved as a word.
**	PARAMETERS
**	#1. The pointer to struct (split);
**	#2. The pointer of command line (cmd);
**	RETURN VALUES
**	-
*/
void	make_words(t_split *split, char *cmd)
{
	int	first_type_char;
	int	i;

	i = 0;
	while (i < split->num_word)
	{
		first_type_char = find_first_reserved_char(cmd);
		if (first_type_char == -1)
			split->words[i++] = ft_substr(cmd, 0, ft_strlen(cmd) + 1);
		else if (first_type_char == S_QUOTE || first_type_char == D_QUOTE)
			save_word_with_quotes(split, &cmd, &i);
		else
			save_reserved_word(split, &cmd, &i);
	}
	split->words[i] = NULL;
}

/*	COUNT_CMD_WORDS
**	------------
**	DESCRIPTION
**	Count the number of words considering space, pipe and redirectors as
**	dividers. Inside quotes, the count is not done.
**	PARAMETERS
**	#1. The pointer of command line (cmd);
**	RETURN VALUES
**	Return number of words.
*/
int	count_cmd_words(char *cmd)
{
	int		word_count;
	bool	is_word;

	word_count = 0;
	is_word = false;
	while (*cmd)
	{
		skip_quotes(&cmd);
		is_word = check_reserved_word(&cmd, &word_count, is_word);
		cmd++;
	}
	if (is_word)
		word_count++;
	return (word_count);
}

/*	SPLIT_CMD
**	------------
**	DESCRIPTION
**	Splits the command line having the space char, pipe and redirectors as the
**	divisor. If these characters are inside quotes it is not split.
**	PARAMETERS
**	#1. The pointer of command line (cmd);
**	RETURN VALUES
**	Return allocated memory from new array of string.
*/
char	**split_cmd(char *cmd)
{
	t_split	split;

	if (!cmd)
		return (NULL);
	split.num_word = count_cmd_words(cmd);
	if (!split.num_word)
		return (NULL);
	split.words = (char **)malloc(((sizeof(char *)) * (split.num_word + 1)));
	if (!split.words)
		return (NULL);
	make_words(&split, cmd);
	return (split.words);
}
