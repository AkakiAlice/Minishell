/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 23:52:12 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/24 16:55:30 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	NO_SUCH_FILE_EXIT
**	------------
**	DESCRIPTION
**	Displays the error message "Is a directory" and terminates the process.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (head_env);
**	RETURN VALUES
**	-
*/
void	is_dir_exit(t_data *data, t_env **head_env, char *word)
{
	ft_putstr_fd("minishell: ", 2);
	put_msg(word, IS_DIR, 2);
	free_minishell(data);
	free_env_lst(head_env);
	exit(126);
}

/*	NO_SUCH_FILE_EXIT
**	------------
**	DESCRIPTION
**	Displays the error message "No such file or directory"
**	and terminates the process.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (head_env);
**	RETURN VALUES
**	-
*/
void	no_such_file_exit(t_data *data, t_env **head_env, char *word)
{
	ft_putstr_fd("minishell: ", 2);
	put_msg(word, NO_FILE_DIR, 2);
	free_minishell(data);
	free_env_lst(head_env);
	exit(127);
}

/*	CHECK_IS_DIR
**	------------
**	DESCRIPTION
**	Checks if the argument received from the terminal is a dir or an executable.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (head_env);
**	RETURN VALUES
**	-
*/
void	check_is_dir(char *word, t_env **head_env, t_data *data)
{
	DIR	*dir;

	dir = opendir(word);
	if (dir)
	{
		closedir(dir);
		is_dir_exit(data, head_env, word);
	}
	else if ((ENOENT == errno && data->cmd_path == NULL)
		|| (access(word, X_OK) == -1))
	{
		no_such_file_exit(data, head_env, word);
	}
	else if ((access(word, X_OK) == 0))
		data->cmd_path = word;
}

/*	EXEC_CMD
**	------------
**	DESCRIPTION
**	Executes the command received from the terminal with execve function.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (head_env);
**	RETURN VALUES
**	-
*/
void	exec_cmd(t_data *data, t_env **head_env, char **word)
{
	if (data->cmd_path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		put_msg(word[0], CMD_NOT_FOUND, 2);
		free_minishell(data);
		free_env_lst(head_env);
		exit(127);
	}
	execve(data->cmd_path, word, NULL);
}

/*	FORK_IT
**	------------
**	DESCRIPTION
**	Creates a child process.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (head_env);
**	RETURN VALUES
**	-
*/
void	fork_it(t_data *data, t_env **head_env)
{
	int			pid[1024];
	int			id;
	t_cmdtable	*head;

	head = data->head_cmd;
	id = -1;
	open_pipe(data);
	while (head != NULL)
	{
		pid[++id] = fork();
		if (pid[id] == 0)
		{
			check_cmd(data, head->word);
			if (ft_strchr(head->word[0], '/') != NULL)
				check_is_dir(head->word[0], head_env, data);
			dup_fds(head);
			close_list_fds(head);
			exec_cmd(data, head_env, head->word);
		}
		close_node_fds(head);
		head = head->next;
	}
	wait_all_pids(pid, id, data);
	free_cmd_lst(&data->head_cmd);
}
