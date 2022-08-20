/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 06:26:03 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/18 07:43:37 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ! Função temporária
void	matrix_printf(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (*(matrix + i))
	{
		ft_printf("[%s]\n", *(matrix + i));
		i++;
	}
	return ;
}

void	open_less(t_cmdtable *cmd_table)
{
	int		i;
	char	*line;

	i = 0;
	while (cmd_table->less[i])
	{
		if (get_token(cmd_table->less[i]) == INPUT)
		{
			// close(cmd_table->fd_in);
			// cmd_table->fd_in = open(cmd_table->less[++i], O_RDONLY);
			// if (cmd_table->fd_in == -1) // Verifica se o arquivo existe
			// 	errno
		}
		else if (get_token(cmd_table->less[i]) == HEREDOC)
		{
			line = readline("> ");
			while (1)
			{
				if (!line)
					break;
				ft_putendl_fd(line, 0); // Preciso alterar o fd
				free(line);
				line = readline("> ");
			}
		}
		i++;
	}
}

void	open_great(t_cmdtable *cmd_table)
{
	int	i;

	i = 0;
	while (cmd_table->great[i])
	{
		if (get_token(cmd_table->great[i]) == TRUNC)
		{
			// close(cmd_table->fd_out);
			// cmd_table->fd_out = open(cmd_table->great[++i], O_CREAT | O_RDWR | O_TRUNC, 0777);
			// if (cmd_table->fd_out == -1) // Verifica se o arquivo existe
			// 	errno
		}
		else if (get_token(cmd_table->great[i]) == APPEND)
		{
			// close(cmd_table->fd_out);
			// cmd_table->fd_out = open(cmd_table->great[++i], O_CREAT | O_RDWR | O_APPEND, 0777);
			// if (cmd_table->fd_out == -1) // Verifica se o arquivo existe
			// 	errno
		}
		i++;
	}
}


void	open_redirection(t_data *data)
{
	t_cmdtable	*head_cmd;

	head_cmd = data->head_cmd;
	while (head_cmd != NULL)
	{
		if (head_cmd->less) {
			ft_printf("Is Less\n");
			open_less(head_cmd);
		}
		if (head_cmd->great) {
			ft_printf("Is Great\n");
			// open_great(head_cmd);
		}
		head_cmd = head_cmd->next;
	}
}
