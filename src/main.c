/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:33:28 by alida-si          #+#    #+#             */
/*   Updated: 2022/06/25 01:36:21 by alida-si         ###   ########.fr       */
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
	}
	else
		exit(0);
}

void	tokenizer(t_data *data)
{
	int	i = 0;
	data->splited_cmdl = ft_split2(data->cmd_line, ' ');
	while (data->splited_cmdl[i] != NULL)
	{
		ft_printf("%s\n", data->splited_cmdl[i]);
		i++;
	}
}

void	free_matrix(char **ptr)
{
	int	i;

	if (ptr != NULL)
	{
		i = 0;
		while (ptr[i])
		{
			free(ptr[i]);
			i++;
		}
		free(ptr);
	}
}

int	main(void)
{
	t_data	data;

	while(1)
	{
		get_prompt(&data);
		tokenizer(&data);
		free(data.cmd_line);
		free_matrix(data.splited_cmdl);
	}
	return (0);
}
