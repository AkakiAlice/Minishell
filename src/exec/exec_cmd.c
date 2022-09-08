/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 23:52:12 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/24 17:52:29 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	CHECK_IS_DIR
**	------------
**	DESCRIPTION
**	Checks if the argument received from the terminal is a dir or an executable.
**	PARAMETERS
**	#1. The name of the directory (word);
**	RETURN VALUES
**	-
*/
void	check_is_dir(char *word)
{
	DIR	*dir;

	dir = opendir(word);
	if (dir)
	{
		closedir(dir);
		is_dir_exit(word);
	}
	else if ((ENOENT == errno && g_data.cmd_path == NULL)
		|| (access(word, X_OK) == -1))
		no_such_file_exit(word, 127);
	else if ((access(word, X_OK) == 0))
		g_data.cmd_path = word;
}

/*	EXEC_CMD
**	------------
**	DESCRIPTION
**	Executes the command received from the terminal with execve function.
**	PARAMETERS
**	#1. The pointer to list (head_table);
**	RETURN VALUES
**	-
*/
void	exec_cmd(t_cmdtable *head_table)
{
	exec_builtin_child(head_table);
	if (g_data.cmd_path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		put_msg(head_table->word[0], CMD_NOT_FOUND, 2);
		free_minishell();
		free_env_lst(&g_data.head_env);
		exit(127);
	}
	execve(g_data.cmd_path, head_table->word, NULL);
}

/*	CHECK_REDIRECT
**	------------
**	DESCRIPTION
**	Checks the redirect.
**	PARAMETERS
**	#1. The pointer to list (head);
**	RETURN VALUES
**	-
*/
void	check_redirect(t_cmdtable *head)
{
	if (!head->err_file)
		return ;
	if (head->err_nb == ENOENT)
		no_such_file_exit(head->err_file, 1);
	if (head->err_nb == EACCES)
		invalid_permission_exit(head->err_file, 1);
}

/*	CHILD_PROCESS
**	------------
**	DESCRIPTION
**	Checks the redirect and command, then executes the commands.
**	PARAMETERS
**	#1. The pointer to list (head);
**	RETURN VALUES
**	-
*/
void	child_process(t_cmdtable *head)
{
	check_redirect(head);
	check_cmd(head->word);
	if (ft_strchr(head->word[0], '/') != NULL)
		check_is_dir(head->word[0]);
	dup_fds(head);
	close_list_fds(head);
	exec_cmd(head);
}

/*	FORK_IT
**	------------
**	DESCRIPTION
**	Creates a child process.
**	PARAMETERS
**	-
**	RETURN VALUES
**	-
*/
void	fork_it(void)
{
	int			pid[1024];
	int			id;
	t_cmdtable	*head;

	head = g_data.head_cmd;
	id = -1;
	while (head != NULL)
	{
		signal(SIGINT, sig_handle_exec_parent);
		signal(SIGQUIT, sig_handle_exec_parent);
		if (!check_builtin(head))
		{
			pid[++id] = fork();
			if (pid[id] == 0)
				child_process(head);
		}
		close_node_fds(head);
		head = head->next;
	}
	wait_all_pids(pid, id);
	free_cmd_lst(&g_data.head_cmd);
}
