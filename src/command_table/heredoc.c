/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:58:48 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/21 20:04:36 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	STRCMP_EQ
**	------------
**	DESCRIPTION
**	Checks if the strings are the same character and length.
**	PARAMETERS
**	#1. The string (s1);
**	#2. The string (s2);
**	RETURN VALUES
**	Return 1 if strings are equal and 0 if it's different.
*/
static int	strcmp_eq(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (*(s1 + i) || *(s2 + i))
	{
		if (*(s1 + i) != *(s2 + i))
			return (0);
		i++;
	}
	return (1);
}

/*	EXEC_HEREDOC
**	------------
**	DESCRIPTION
**	Exec heredoc.
**	PARAMETERS
**	#1. The pointer to struct "head_cmd" (head_cmd);
**	#2. The string (eof);
**	RETURN VALUES
**	-
*/
void	exec_heredoc(t_cmdtable *head_cmd, char *eof)
{
	char	*line;
	int		fd[2];

	line = readline("> ");
	pipe(fd);
	while (1)
	{
		if (strcmp_eq(eof, line))
		{
			free(line);
			head_cmd->fdin = fd[0];
			close(fd[1]);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
}
