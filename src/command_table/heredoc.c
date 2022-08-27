/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:58:48 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/27 19:04:12 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_heredoc(int signum)
{
	if (signum == 2)
	{
		g_data.signal = 130;
		ft_printf("\n");
		//free(g_data.line);
		//head_cmd->fdin = g_data.fd_pipe[0];
		close(0);
		//close(g_data.fd_pipe[1]);
		g_data.flag = 1;
	}
	/*close(0);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_data.signal = 130;*/
	(void)signum;
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
	g_data.flag = 0;
	signal(SIGINT, sig_heredoc);
	g_data.line = readline("> ");
	pipe(g_data.fd_pipe);
	while (1)
	{
		//signal(SIGINT, sighandler);
		if (strcmp_eq(eof, g_data.line))
		{
			free(g_data.line);
			head_cmd->fdin = g_data.fd_pipe[0];
			close(g_data.fd_pipe[1]);
			break ;
		}
		if (g_data.flag == 1)
		{
			head_cmd->fdin = g_data.fd_pipe[0];
			break ;
		}
		if (g_data.line && g_data.flag == 0)
		{
			write(g_data.fd_pipe[1], g_data.line, ft_strlen(g_data.line));
			write(g_data.fd_pipe[1], "\n", 1);
			free(g_data.line);
		}
		g_data.line = readline("-> ");
	}
}

/*void	exec_heredoc(t_cmdtable *head_cmd, char *eof)
{
	char	*line;
	int		fd[2];

	signal(SIGINT, sig_heredoc);
	line = readline("> ");
	pipe(fd);
	while (1)
	{
		//signal(SIGINT, sighandler);
		if (strcmp_eq(eof, line))
		{
			free(line);
			head_cmd->fdin = fd[0];
			close(fd[1]);
			break ;
		}
		if (line)
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		line = readline("> ");
	}
}*/
