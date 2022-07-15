/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 23:52:12 by alida-si          #+#    #+#             */
/*   Updated: 2022/07/15 04:01:44 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *data)
{
	if (data->cmd_path == NULL)
	{
		write(2, data->splited_cmdl[0], ft_strlen(data->splited_cmdl[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	execve(data->cmd_path, data->splited_cmdl, NULL);
}

void	fork_it(t_data *data)
{
	int	pid;
	int	p_status;

	pid = fork();
	if (pid == 0)
		exec_cmd(data);
	waitpid(0, &data->status, 0);
	if (WIFEXITED(data->status))
		p_status = WEXITSTATUS(data->status);
	ft_printf("%i\n",p_status);
}
