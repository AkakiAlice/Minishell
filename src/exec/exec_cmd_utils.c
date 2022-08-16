/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:31:08 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/16 17:09:21 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipe(t_data *data)
{
	int			pipe_fd[2];
	t_cmdtable	*temp;

	temp = data->head_cmd;
	while (temp != NULL)
	{
		if (temp->next != NULL)
		{
			pipe(pipe_fd);
			temp->fdout = pipe_fd[1];
			temp->next->fdin = pipe_fd[0];
		}
		temp = temp->next;
	}
}

void	wait_all_pids(int pid[1024], int id, t_data *data)
{
	int	p_status;
	int	j;

	p_status = 0;
	j = 0;
	while (j <= id)
	{
		waitpid(pid[j], &data->status, 0);
		j++;
	}
	if (WIFEXITED(data->status))
		p_status = WEXITSTATUS(data->status);
	data->status = p_status;
}

void	close_node_fds(t_cmdtable *head)
{
	if (head->fdout > 2)
		close(head->fdout);
	if (head->fdin > 2)
		close(head->fdin);
}

void	close_list_fds(t_cmdtable *head)
{
	while (head)
	{
		close_node_fds(head);
		head = head->next;
	}
}

void	dup_fds(t_cmdtable *head)
{
	if (head->fdout > 2)
		dup2(head->fdout, 1);
	if (head->fdin > 2)
		dup2(head->fdin, 0);
}
