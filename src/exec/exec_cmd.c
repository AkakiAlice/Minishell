/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 23:52:12 by alida-si          #+#    #+#             */
/*   Updated: 2022/07/22 16:47:17 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	NO_SUCH_FILE_EXIT
**	------------
**	DESCRIPTION
**	Displays the error message "Is a directory" and terminates the process.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (last_env);
**	RETURN VALUES
**	-
*/
void	is_dir_exit(t_data *data, t_env **last_env)
{
	write(2, data->splited_cmdl[0], ft_strlen(data->splited_cmdl[0]));
	write(2, ": Is a directory\n", 17);
	ft_matrix_free(data->splited_cmdl);
	free_env_lst(last_env);
	exit(126);
}

/*	NO_SUCH_FILE_EXIT
**	------------
**	DESCRIPTION
**	Displays the error message "No such file or directory"
**	and terminates the process.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (last_env);
**	RETURN VALUES
**	-
*/
void	no_such_file_exit(t_data *data, t_env **last_env)
{
	write(2, data->splited_cmdl[0], ft_strlen(data->splited_cmdl[0]));
	write(2, ": No such file or directory\n", 28);
	ft_matrix_free(data->splited_cmdl);
	free_env_lst(last_env);
	exit(127);
}

/*	CHECK_IS_DIR
**	------------
**	DESCRIPTION
**	Checks if the argument received from the terminal is a dir or an executable.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (last_env);
**	RETURN VALUES
**	-
*/
void	check_is_dir(t_data *data, t_env **last_env)
{
	DIR	*dir;

	dir = opendir(data->splited_cmdl[0]);
	if (dir)
	{
		closedir(dir);
		is_dir_exit(data, last_env);
	}
	else if ((ENOENT == errno && data->cmd_path == NULL)
		|| (access(data->splited_cmdl[0], X_OK) == -1))
	{
		no_such_file_exit(data, last_env);
	}
	else if ((access(data->splited_cmdl[0], X_OK) == 0))
		data->cmd_path = data->splited_cmdl[0];
}

/*	EXEC_CMD
**	------------
**	DESCRIPTION
**	Executes the command received from the terminal with execve function.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (last_env);
**	RETURN VALUES
**	-
*/
void	exec_cmd(t_data *data, t_env **last_env)
{
	if (data->cmd_path == NULL)
	{
		write(2, data->splited_cmdl[0], ft_strlen(data->splited_cmdl[0]));
		write(2, ": command not found\n", 20);
		free_env_lst(last_env);
		ft_matrix_free(data->splited_cmdl);
		exit(127);
	}
	execve(data->cmd_path, data->splited_cmdl, NULL);
}

/*	FORK_IT
**	------------
**	DESCRIPTION
**	Creates a child process.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (last_env);
**	RETURN VALUES
**	-
*/
void	fork_it(t_data *data, t_env **last_env)
{
	int	pid;
	int	p_status;

	pid = fork();
	if (pid == 0)
	{
		if (ft_strchr(data->splited_cmdl[0], '/') != NULL)
			check_is_dir(data, last_env);
		exec_cmd(data, last_env);
	}
	waitpid(0, &data->status, 0);
	if (WIFEXITED(data->status))
		p_status = WEXITSTATUS(data->status);
	data->status = p_status;
}
