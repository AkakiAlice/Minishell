/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:58:48 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/28 15:01:48 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_sig(int signal)
{
	g_data.signal = signal;
	write(1, "\n", 1);
	exit(130);
}

void	write_heredoc(char *eof, int *fd)
{
	char	*line;

	signal(SIGINT, child_sig);
	line = readline("> ");
	while (1)
	{
		if (!line)
			break;
		if (strcmp_eq(eof, line))
			break;
		write(*fd, line, ft_strlen(line));
		write(*fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(*fd);
	exit(0);
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
	int		fd[2];
	int		pid;
	int		wstatus;

	if (head_cmd->fdin > 2)
		close(head_cmd->fdin);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		write_heredoc(eof, &fd[1]);
	}
	signal(SIGINT, SIG_IGN);
	close(fd[1]);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 130)
	{
		close(fd[0]);
		g_data.status = 130;
		g_data.interrupt_heredoc = true;
	}
	head_cmd->fdin = fd[0];
}
