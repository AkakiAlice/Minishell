/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 06:26:03 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/20 17:25:39 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp_eq(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (*(s1 + i) || *(s2 + i))
	{
		if (*(s1 + i) != *(s2 + i))
			return (0);
		i++;
	}
	return (1);
}


void	exec_heredoc(t_cmdtable *head_cmd, char *eof)
{
	char	*line;
	int		fd[2];

	line = readline("> ");
	pipe(fd);
	while (1)
	{
		if (ft_strcmp_eq(eof, line))
		{
			free(line);
			head_cmd->fdin = fd[0];
			close(fd[1]);
			break;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
}

void	open_less(t_cmdtable *head_cmd)
{
	int		i;

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
		else if (get_token(head_cmd->less[i]) == HEREDOC)
		{
			exec_heredoc(head_cmd, head_cmd->less[++i]);
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
