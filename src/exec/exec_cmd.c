/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 23:52:12 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/13 14:38:19 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_pipe(int fd)
{
	char	*ret;
	char	*swap;
	char	*temp;

	temp = ft_strdup("");
	while (1)
	{
		ret = get_next_line(fd);
		if (ret == NULL)
			break ;
		swap = temp;
		temp = ft_strjoin(swap, ret);
		free(swap);
		free(ret);
	}
	ft_printf("%s", temp);
}

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
	ft_putstr_fd("minishell: ", 2);
	put_msg(data->head_cmd->word[0], IS_DIR, 2);
	free_minishell(data);
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
	ft_putstr_fd("minishell: ", 2);
	put_msg(data->head_cmd->word[0], NO_FILE_DIR, 2);
	free_minishell(data);
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

	dir = opendir(data->head_cmd->word[0]);
	if (dir)
	{
		closedir(dir);
		is_dir_exit(data, last_env);
	}
	else if ((ENOENT == errno && data->cmd_path == NULL)
		|| (access(data->head_cmd->word[0], X_OK) == -1))
	{
		no_such_file_exit(data, last_env);
	}
	else if ((access(data->head_cmd->word[0], X_OK) == 0))
		data->cmd_path = data->head_cmd->word[0];
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
void	exec_cmd(t_data *data, t_env **last_env, char **word)
{
	check_cmd(data);
	if (data->cmd_path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		put_msg(word[0], CMD_NOT_FOUND, 2);
		free_minishell(data);
		free_env_lst(last_env);
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
**	#2. The pointer to list (last_env);
**	RETURN VALUES
**	-
*/
void	fork_it(t_data *data, t_env **last_env)
{
	int	pid;
	int	p_status;
	int	pipe_fd[2];
	int	index;

	index = 0;
	pipe(pipe_fd);
	while (data->head_cmd != NULL)
	{
		p_status = 0;
		pid = fork();
		if (pid == 0 && index == 0)
		{
			if (ft_strchr(data->head_cmd->word[0], '/') != NULL)
				check_is_dir(data, last_env);
			dup2(pipe_fd[1], 1);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exec_cmd(data, last_env, data->head_cmd->word);
		}
		if (pid == 0 && index == 1)
		{
			if (ft_strchr(data->head_cmd->word[0], '/') != NULL)
				check_is_dir(data, last_env);
			dup2(pipe_fd[0], 0);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exec_cmd(data, last_env, data->head_cmd->word);
		}
		index++;
		data->head_cmd = data->head_cmd->next;
		waitpid(0, &data->status, 0);
		close(pipe_fd[1]);
		if (WIFEXITED(data->status))
			p_status = WEXITSTATUS(data->status);
		data->status = p_status;
	}
}


/*void	fork_it(t_data *data, t_env **last_env)
{
	int	pid;
	int	p_status;
	int	pipe_fd[2];

	pipe(pipe_fd);
	p_status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (ft_strchr(data->head_cmd->word[0], '/') != NULL)
			check_is_dir(data, last_env);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exec_cmd(data, last_env, data->head_cmd->word);
	}
	waitpid(0, &data->status, 0);
	close(pipe_fd[1]);
	if (WIFEXITED(data->status))
		p_status = WEXITSTATUS(data->status);
	data->status = p_status;
	pid = fork();
	if (pid == 0)
	{
		dup2(pipe_fd[0], 0);
		execlp("wc", "wc", "-l", NULL);
	}
	//read_pipe(pipe_fd[0]);
}*/