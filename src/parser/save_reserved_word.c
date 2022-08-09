/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_reserved_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 06:27:33 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/09 06:30:15 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	STRCHR_RESERVED
**	------------
**	DESCRIPTION
**	Find the first reserved character within the string.
**	PARAMETERS
**	#1. The pointer of command line (cmd);
**	RETURN VALUES
**	Returns the found character pointer.
*/
char	*strchr_reserved(char *cmd)
{
	while (*cmd != '\0')
	{
		if (is_reserved_word(*cmd) != -1)
			return (cmd);
		cmd++;
	}
	return (NULL);
}

/*	STRLEN_RESERVED_WORD
**	------------
**	DESCRIPTION
**	Determines the size of the reserved word.
**	PARAMETERS
**	#1. The string (str);
**	RETURN VALUES
**	Return string length
*/
int	strlen_reserved_word(char *str)
{
	if (ft_strncmp_eq(str, "<<", 2))
		return (2);
	else if (ft_strncmp_eq(str, ">>", 2))
		return (2);
	return (1);
}

/*	STRCHR_RESERVED
**	------------
**	DESCRIPTION
**	Save the reserved word. The word before the reserved character is also
**	saved.
**	PARAMETERS
**	#1. The pointer to struct (split);
**	#2. The pointer of command line (cmd);
**	#3. The pointer to word index (i);
**	RETURN VALUES
**	-
*/
void	save_reserved_word(t_split *split, char **cmd, int *i)
{
	char	*reserve_char;
	int		size;

	reserve_char = strchr_reserved(*cmd);
	if (reserve_char == NULL)
		return ;
	size = reserve_char - *cmd;
	if (size != 0)
		split->words[(*i)++] = ft_substr(*cmd, 0, size);
	if (*reserve_char == SPC)
		while (*reserve_char == SPC)
			reserve_char++;
	else
	{
		size = strlen_reserved_word(reserve_char);
		split->words[(*i)++] = ft_substr(reserve_char, 0, size);
		reserve_char += size;
	}
	*cmd = reserve_char;
}
