/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 05:57:11 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/25 06:17:38 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	matrix_len(char **matrix)
{
	size_t	i;

	i = 0;
	while (*(matrix + i))
		i++;
	return (i);
}

bool	str_is_numeric(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '+' && *str != '-')
			return (false);
		str++;
	}
	return (true);
}

void	put_msg_cmd(char *title, char *cmd, char *msg, int fd)
{
	ft_putstr_fd(title, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(msg, fd);
	return ;
}

void	exit_cmd(t_data *data, t_cmdtable *head_table)
{
	int	i;
	int	status;

	i = 1;
	status = -1;
	ft_putendl_fd("exit", 2);
	while (head_table->word[i])
	{
		if (status != -1)
		{
			data->status = 1;
			put_msg_cmd("minishell", "exit", TOO_MANY_ARG, 2);
			return ;
		}
		if (str_is_numeric(head_table->word[i]))
		{
			status = ft_atoi(head_table->word[i]);
			if (status < 0 || status > 255)
				status = 128;
		}
		i++;
	}
	if (status != -1)
		data->status = status;
	free_minishell(data);
	free_env_lst(&data->head_env);
	exit(data->status);
}
