/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 06:26:03 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/20 15:56:58 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	open_less(t_cmdtable *head_cmd)
{
	int		i;
	// char	*line;

	i = 0;
	while (head_cmd->less[i])
	{
		if (get_token(head_cmd->less[i]) == INPUT)
		{
			if (head_cmd->fdin > 2)
				close(head_cmd->fdin);
			head_cmd->fdin = open(head_cmd->less[++i], O_RDONLY);
			if (head_cmd->fdin == -1)
			{
				head_cmd->err_less_file = ft_strdup(head_cmd->less[i]);
				break ;
			}
		}
		// else if (get_token(data->head_cmd->less[i]) == HEREDOC)
		// {
		// 	line = readline("> ");
		// 	while (1)
		// 	{
		// 		if (!line)
		// 			break;
		// 		ft_putendl_fd(line, 0); // Preciso alterar o fd
		// 		free(line);
		// 		line = readline("> ");
		// 	}
		// }
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
			if (cmd_table->fdout > 2)
				close(cmd_table->fdout);
			cmd_table->fdout = open(cmd_table->great[++i], O_CREAT | O_RDWR | O_TRUNC, 0777);
			if (cmd_table->fdout == -1)
			{
				cmd_table->err_great_file = ft_strdup(cmd_table->great[i]);
				break ;
			}
		}
		else if (get_token(cmd_table->great[i]) == APPEND)
		{
			if (cmd_table->fdout > 2)
				close(cmd_table->fdout);
			cmd_table->fdout = open(cmd_table->great[++i], O_CREAT | O_RDWR | O_APPEND, 0777);
			if (cmd_table->fdout == -1)
			{
				cmd_table->err_great_file = ft_strdup(cmd_table->great[i]);
				break ;
			}
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
		if (head_cmd->less)
			open_less(head_cmd);
		if (head_cmd->great)
			open_great(head_cmd);
		head_cmd = head_cmd->next;
	}
}
