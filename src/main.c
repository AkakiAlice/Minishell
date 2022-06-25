/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:33:28 by alida-si          #+#    #+#             */
/*   Updated: 2022/06/25 15:36:31 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
