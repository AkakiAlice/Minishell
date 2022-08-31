/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:58:48 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/31 07:33:05 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	PUT_MSG_HEREDOC
**	------------
**	DESCRIPTION
**	Put message in 'title: alert: description' format.
**	PARAMETERS
**	#1. The limiter word (eof);
**	#2. The file descriptor (fd);
**	RETURN VALUES
**	-
*/
static void	put_msg_heredoc(char *eof, int fd)
{
	ft_putstr_fd("minishell", fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd("warning", fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(QUIT_HEREDOC, fd);
	ft_putstr_fd(" (wanted `", fd);
	ft_putstr_fd(eof, fd);
	ft_putendl_fd("')", fd);
	return ;
}

/*	WRITE_HEREDOC
**	------------
**	DESCRIPTION
**	Write heredoc in file descriptor.
**	PARAMETERS
**	#1. The string (eof);
**	#2. The pointer to file descriptor (fd);
**	RETURN VALUES
**	-
*/
void	write_heredoc(char *eof, int *fd)
{
	char	*line;

	signal(SIGINT, sig_handle_heredoc_child);
	line = readline("> ");
	while (1)
	{
		if (!line)
		{
			put_msg_heredoc(eof, 2);
			clear_minishell();
			exit(1);
		}
		if (strcmp_eq(eof, line))
			break ;
		write(*fd, line, ft_strlen(line));
		write(*fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(*fd);
	clear_minishell();
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
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 1)
		g_data.interrupt_heredoc = true;
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 130)
	{
		close(fd[0]);
		g_data.status = 130;
		g_data.interrupt_heredoc = true;
	}
	head_cmd->fdin = fd[0];
}
