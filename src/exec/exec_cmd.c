/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 23:52:12 by alida-si          #+#    #+#             */
/*   Updated: 2022/07/19 18:00:29 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_is_dir(t_data *data, t_env **last_env)
{
	DIR	*dir;

	dir = opendir(data->splited_cmdl[0]);
	if (dir)
	{
		write(2, data->splited_cmdl[0], ft_strlen(data->splited_cmdl[0]));
		write(2, ": Is a directory\n", 17);
		closedir(dir);
		ft_matrix_free(data->splited_cmdl);
		free_env_lst(last_env);
		exit(126);
	}
	else if (ENOENT == errno && data->cmd_path == NULL)
	{
		write(2, data->splited_cmdl[0], ft_strlen(data->splited_cmdl[0]));
		write(2, ": No such file or directory\n", 28);
		ft_matrix_free(data->splited_cmdl);
		free_env_lst(last_env);
		exit(127);
	}
	else if ((access(data->splited_cmdl[0], X_OK) == 0))
		data->cmd_path = data->splited_cmdl[0];
}

void	exec_cmd(t_data *data, t_env **last_env)
{
	if (data->splited_cmdl[0][0] == '/')
		check_is_dir(data, last_env);
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

void	fork_it(t_data *data, t_env **last_env)
{
	int	pid;
	int	p_status;

	pid = fork();
	if (pid == 0)
		exec_cmd(data, last_env);
	waitpid(0, &data->status, 0);
	if (WIFEXITED(data->status))
		p_status = WEXITSTATUS(data->status);
	ft_printf("%i\n", p_status);
}
