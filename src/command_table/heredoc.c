/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:58:48 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/29 16:10:17 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_minishell()
{
	if (g_data.cmd_line != NULL)
	{
		free(g_data.cmd_line);
		g_data.cmd_line = NULL;
	}
	ft_matrix_free(&g_data.splited_cmdl);
	g_data.splited_cmdl = NULL;
	free_env_lst(&g_data.head_env);
	free_token_lst(&g_data.head_token);
	free_cmd_lst(&g_data.head_cmd);
	g_data.is_pipe = false;
	g_data.signal = 0;
	g_data.interrupt_heredoc = false;
}

static void	child_sig(int signal)
{
	g_data.signal = signal;
	write(1, "\n", 1);
	clear_minishell();
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
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("warning: ", 2);
			ft_putstr_fd("here-document delimited by end-of-file ", 2);
			ft_printf("(wanted `%s')\n", eof);
			clear_minishell();
			exit(1);
		}
		if (strcmp_eq(eof, line))
			break;
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
