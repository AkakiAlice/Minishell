/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 06:26:03 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/21 20:06:03 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	OPEN_LESS
**	------------
**	DESCRIPTION
**	Open less redirects. In case of error, save the filename and errno.
**	PARAMETERS
**	#1. The pointer to struct "head_cmd" (head_cmd);
**	#2. The string filename (filename);
**	RETURN VALUES
**	-
*/
static void	open_less(t_cmdtable *head_cmd, char *filename)
{
	if (head_cmd->fdin > 2)
		close(head_cmd->fdin);
	head_cmd->fdin = open(filename, O_RDONLY);
	if (head_cmd->fdin == -1)
	{
		head_cmd->err_file = ft_strdup(filename);
		head_cmd->err_nb = errno;
	}
}

/*	OPEN_GREAT
**	------------
**	DESCRIPTION
**	Open great redirects. In case of error, save the filename and errno.
**	PARAMETERS
**	#1. The pointer to struct "head_cmd" (head_cmd);
**	#2. The string filename (filename);
**	#3. The integer (oflag);
**	RETURN VALUES
**	-
*/
static void	open_great(t_cmdtable *head_cmd, char *filename, int oflag)
{
	if (head_cmd->fdout > 2)
		close(head_cmd->fdout);
	head_cmd->fdout = open(filename, O_CREAT | O_RDWR | oflag, 0777);
	if (head_cmd->fdout == -1)
	{
		head_cmd->err_file = ft_strdup(filename);
		head_cmd->err_nb = errno;
	}
}

/*	OPEN_REDIRECTION_TABLE
**	------------
**	DESCRIPTION
**	Loops through the array of redirect and opens a redirect.
**	PARAMETERS
**	#1. The pointer to struct "head_cmd" (head_cmd);
**	RETURN VALUES
**	-
*/
static void	open_redirect_table(t_cmdtable *head_cmd)
{
	int	i;
	int	token;

	i = 0;
	while (head_cmd->redirect[i] && head_cmd->err_nb == -1)
	{
		token = get_token(head_cmd->redirect[i]);
		if (token == TRUNC)
			open_great(head_cmd, head_cmd->redirect[++i], O_TRUNC);
		else if (token == APPEND)
			open_great(head_cmd, head_cmd->redirect[++i], O_APPEND);
		else if (token == INPUT)
			open_less(head_cmd, head_cmd->redirect[++i]);
		else if (token == HEREDOC)
			exec_heredoc(head_cmd, head_cmd->redirect[++i]);
		i++;
	}
}

/*	OPEN_REDIRECTION
**	------------
**	DESCRIPTION
**	Loops through the linked list of commands and opens a redirect to each node.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	RETURN VALUES
**	-
*/
void	open_redirection(t_data *data)
{
	t_cmdtable	*head_cmd;

	head_cmd = data->head_cmd;
	while (head_cmd != NULL)
	{
		if (head_cmd->redirect)
			open_redirect_table(head_cmd);
		head_cmd = head_cmd->next;
	}
}
