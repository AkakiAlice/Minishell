/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:23:48 by alida-si          #+#    #+#             */
/*   Updated: 2022/06/27 13:54:14 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_prompt(t_data *data)
{
	char	*cwd;
	char	*aux;

	cwd = getcwd(NULL, 0);
	aux = ft_strdup("$ ");
	ft_strlcat(cwd, aux, (ft_strlen(cwd) + 3));
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
		ft_matrix_free(data->splited_cmdl);
		exit(0);
	}
}
