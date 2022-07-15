/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:52:08 by alida-si          #+#    #+#             */
/*   Updated: 2022/07/14 19:12:25 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(char *env_value, t_data *data)
{
	char	**path_list;
	char	*aux;
	int		i;

	path_list = ft_split(env_value, ':');
	aux = ft_strcat("/", data->splited_cmdl[0]);
	i = 0;
	while (path_list[i])
	{
		data->cmd_path = ft_strcat(path_list[i], aux);
		if ((access(data->cmd_path, F_OK) == 0))
		{
			break ;
		}
		free(data->cmd_path);
		i++;
	}
	free(aux);
}
