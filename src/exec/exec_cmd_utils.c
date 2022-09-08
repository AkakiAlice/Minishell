/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:31:08 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/08 14:03:34 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	OPEN_PIPE
**	------------
**	DESCRIPTION
**	Loops through the linked list of commands and opens a pipe to each node.
**	PARAMETERS
**	-
**	RETURN VALUES
**	-
*/
void	open_pipe(void)
{
	int			pipe_fd[2];
	t_cmdtable	*temp;

	temp = g_data.head_cmd;
	while (temp != NULL)
	{
		if (temp->next != NULL)
		{
			pipe(pipe_fd);
			temp->fdout = pipe_fd[1];
			temp->next->fdin = pipe_fd[0];
			g_data.is_pipe = true;
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
**	RETURN VALUES
**	-
*/
void	wait_all_pids(int pid[1024], int id)
{
	int	p_status;
	int	j;

	j = 0;
	p_status = 0;
	if (id == -1)
		return ;
	while (j <= id)
	{
		waitpid(pid[j], &p_status, 0);
		j++;
	}
	if (WIFEXITED(p_status))
		g_data.status = WEXITSTATUS(p_status);
}

/*	CLOSE_NODE_FDS
**	------------
**	DESCRIPTION
**	Closes file descriptors from one node.
**	PARAMETERS
**	#1. The command table linked list (head);
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
**	#1. The command table linked list (head);
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
**	#1. The command table linked list (head);
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
