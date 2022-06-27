/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:23:48 by alida-si          #+#    #+#             */
/*   Updated: 2022/06/27 14:52:16 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_prompt(t_data *data)
{
	char	*cwd;
	char	aux[1024];

	getcwd(aux, sizeof(aux));
	cwd = ft_strcat(aux, "$ ");
	data->cmd_line = readline(cwd);
	if (*data->cmd_line)
	{
		add_history(data->cmd_line);
		free(cwd);
	}
	else
	{
		free(cwd);
		free(data->cmd_line);
		exit(0);
	}
}
