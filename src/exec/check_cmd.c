/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:52:08 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/03 13:19:31 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	CHECK_CMD
**	------------
**	DESCRIPTION
**	Checks if the cmd received from the terminal exists in the PATH variable.
**	PARAMETERS
**	#1. The pointer to PATH value (env_value);
**	#2. The pointer to struct "data" (data);
**	RETURN VALUES
**	-
*/
void	check_cmd(t_data *data, char **word)
{
	char	**path_list;
	char	*aux;
	int		i;

	data->path_value = get_path(data->head_env);
	if (data->path_value != NULL)
	{
		path_list = ft_split(data->path_value, ':');
		aux = ft_strcat("/", word[0]);
		i = 0;
		while (path_list[i])
		{
			data->cmd_path = ft_strcat(path_list[i], aux);
			if ((access(data->cmd_path, F_OK) == 0))
			{
				break ;
			}
			free(data->cmd_path);
			data->cmd_path = NULL;
			i++;
		}
		free(aux);
		ft_matrix_free(&path_list);
	}
}
