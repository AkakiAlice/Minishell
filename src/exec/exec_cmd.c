/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 23:52:12 by alida-si          #+#    #+#             */
/*   Updated: 2022/07/07 01:47:37 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *data)
{
	char	*path="/bin/ls";

	execve(path, data->splited_cmdl, NULL);
}

void	fork_it(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exec_cmd(data);
	waitpid(0, NULL, 0);
}