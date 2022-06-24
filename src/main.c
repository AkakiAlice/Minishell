/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:33:28 by alida-si          #+#    #+#             */
/*   Updated: 2022/06/25 00:56:08 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_prompt(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_strlcat(cwd, "$ ", (ft_strlen(cwd) + 3));
	data->cmd_line = readline(cwd);
	if (*data->cmd_line)
	{
		add_history(data->cmd_line);
		free(data->cmd_line);
	}
	else
		exit(0);
}

int	main(void)
{
	t_data	data;

	while(1)
	{
		get_prompt(&data);
	}
	return (0);
}
