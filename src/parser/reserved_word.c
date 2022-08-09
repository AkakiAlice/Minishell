/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserved_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 06:20:36 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/09 06:22:44 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	IS_RESERVED_WORD
**	------------
**	DESCRIPTION
**	Checks if the character belongs to reserved word.
**	PARAMETERS
**	#1. The character (c);
**	RETURN VALUES
**	Returns the type of reserved word.
*/
int	is_reserved_word(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '<')
		return (INPUT);
	if (c == '>')
		return (TRUNC);
	if (c == ' ')
		return (SPC);
	return (-1);
}

/*	CHECK_RESERVED_WORD
**	------------
**	DESCRIPTION
**	Checks if the character is a reserved word and counts.
**	PARAMETERS
**	#1. The pointer of command line (cmd);
**	#2. The pointer of counter (word_count);
**	#3. The flag of is word (is_word);
**	RETURN VALUES
**	Return true if it is a non-reserved word ans false if it is a reserved word
*/
bool	check_reserved_word(char **cmd, int *word_count, bool is_word)
{
	int	reserved_word;

	reserved_word = is_reserved_word(**cmd);
	if (reserved_word == -1)
		return (true);
	if (is_word)
		(*word_count)++;
	if (ft_strncmp_eq(*cmd, "<<", 2) || ft_strncmp_eq(*cmd, ">>", 2))
		(*cmd)++;
	if (reserved_word != SPC)
		(*word_count)++;
	return (false);
}

/*	FIND_FIRST_RESERVED_WORD
**	------------
**	DESCRIPTION
**	Finds the first occurrence of the reserved word.
**	PARAMETERS
**	#1. The pointer of command line (cmd);
**	RETURN VALUES
**	Returns the type of reserved word it found first.
*/
int	find_first_reserved_char(char *cmd)
{
	int	quote_type;
	int	char_type;

	while (*cmd != '\0')
	{
		quote_type = is_quote_type(*cmd);
		if (quote_type != -1)
			return (quote_type);
		char_type = is_reserved_word(*cmd);
		if (char_type != -1)
			return (char_type);
		cmd++;
	}
	return (-1);
}
