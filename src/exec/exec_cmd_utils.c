/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:31:08 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/28 16:15:55 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	OPEN_PIPE
**	------------
**	DESCRIPTION
**	Loops through the linked list of commands and opens a pipe to each node.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	RETURN VALUES
**	-
*/
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
			data->is_pipe = true;
		}
		temp = temp->next;
	}
}

/*	WAIT_ALL_PIDS
**	------------
**	DESCRIPTION
**	Waits for all child processes looping through process array.
**	PARAMETERS
**	#1. The process array;
**	#2. The number of processes;
**	#3. The pointer to struct "data" (data);
**	RETURN VALUES
**	-
*/
void	wait_all_pids(int pid[1024], int id, t_data *data)
{
	int	p_status;
	int	j;

	p_status = 0;
	j = 0;
	if (id == -1)
		return ;
	while (j <= id)
	{
		waitpid(pid[j], &data->status, 0);
		j++;
	}
	if (WIFEXITED(data->status))
	{
		p_status = WEXITSTATUS(data->status);
	}
	if (data->signal == 2)
		data->status = 130;
	else if (data->signal == 3)
		data->status = 131;
	else
		data->status = p_status;
}

/*	CLOSE_NODE_FDS
**	------------
**	DESCRIPTION
**	Closes file descriptors from one node.
**	PARAMETERS
**	#1. The command table linked list;
**	RETURN VALUES
**	-
*/
void	close_node_fds(t_cmdtable *head)
{
	if (head->fdout > 2)
		close(head->fdout);
	if (head->fdin > 2)
		close(head->fdin);
}

/*	CLOSE_LIST_FDS
**	------------
**	DESCRIPTION
**	Closes file descriptors of all list nodes.
**	PARAMETERS
**	#1. The command table linked list;
**	RETURN VALUES
**	-
*/
void	close_list_fds(t_cmdtable *head)
{
	while (head)
	{
		close_node_fds(head);
		head = head->next;
	}
}

/*	DUP_FDS
**	------------
**	DESCRIPTION
**	Redirects the descriptors of the respective node.
**	PARAMETERS
**	#1. The command table linked list;
**	RETURN VALUES
**	-
*/
void	dup_fds(t_cmdtable *head)
{
	if (head->fdout > 2)
		dup2(head->fdout, 1);
	if (head->fdin > 2)
		dup2(head->fdin, 0);
}
