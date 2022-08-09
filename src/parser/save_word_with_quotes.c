/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_word_with_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 06:25:39 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/09 06:26:16 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	SKIP_NUM_CHAR
**	------------
**	DESCRIPTION
**	Skip characters in the amount num as parameter.
**	PARAMETERS
**	#1. The pointer to string (str);
**	#2. The skip numbers (num);
**	RETURN VALUES
**	-
*/
void	skip_num_char(char **str, int num)
{
	while (**str && num > 0)
	{
		(*str)++;
		num--;
	}
	return ;
}

/*	STRLEN_WITH_QUOTES
**	------------
**	DESCRIPTION
**	Count the number of characters. The count stops when the character is pipe
**	or redirectors outside the quotes.
**	PARAMETERS
**	#1. The pointer of command line (cmd);
**	RETURN VALUES
**	Return string length
*/
int	strlen_with_quotes(char *cmd)
{
	t_quotes	quotes;
	int			size;

	quotes.in = false;
	size = 0;
	while (cmd[size])
	{
		if (!quotes.in)
		{
			if (is_reserved_word(cmd[size]) != -1)
				return (size);
			quotes.type = is_quote_type(cmd[size]);
			if (quotes.type != -1)
				quotes.in = true;
		}
		else if (cmd[size] == quotes.type)
			quotes.in = false;
		size++;
	}
	return (size);
}

/*	SAVE_WORD_WITH_QUOTES
**	------------
**	DESCRIPTION
**	Save the word in quotes and skip the cmd characters.
**	PARAMETERS
**	#1. The pointer to struct (split);
**	#2. The pointer of command line (cmd);
**	#3. The pointer to word index (i);
**	RETURN VALUES
**	-
*/
void	save_word_with_quotes(t_split *split, char **cmd, int *i)
{
	int	size;

	size = strlen_with_quotes(*cmd);
	split->words[(*i)++] = ft_substr(*cmd, 0, size);
	skip_num_char(cmd, size);
}
