/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:05:42 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/16 16:11:34 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	FREE_TOKEN_LST
**	------------
**	DESCRIPTION
**	Free all memory allocated within command singly linked list.
**	PARAMETERS
**	#1. The pointer to the first element of the list (head_cmd);
**	RETURN VALUES
**	-
*/
void	free_cmd_lst(t_cmdtable **head_cmd)
{
	t_cmdtable	*temp;

	if (*head_cmd == NULL)
		return ;
	while (*head_cmd != NULL)
	{
		ft_matrix_free((*head_cmd)->word);
		temp = (*head_cmd)->next;
		free(*head_cmd);
		*head_cmd = temp;
	}
}

/*	CMD_LST_ADD_FRONT
**	------------
**	DESCRIPTION
**	Add the new node at the end of the singly linked list.
**	PARAMETERS
**	#1. The pointer to list (head_cmd);
**	#2. The content that will be inserted into the new node (pipe_line);
**	RETURN VALUES
**	-
*/
void	cmd_lst_add_front(t_cmdtable **head_cmd, char *pipe_line)
{
	t_cmdtable	*ptr;
	t_cmdtable	*temp;

	ptr = (t_cmdtable *)malloc(sizeof(t_cmdtable));
	if (ptr != NULL)
	{
		ptr->word = ft_split2(pipe_line, ' ');
		ptr->fdin = 0;
		ptr->fdout = 1;
		if ((*head_cmd) == NULL)
		{
			ptr -> next = NULL;
			*head_cmd = ptr;
		}
		else
		{
			temp = *head_cmd;
			while (temp -> next != NULL)
			{
				temp = temp -> next;
			}
			temp->next = ptr;
			ptr->next = NULL;
		}
	}
}

/*	CREATE_CMD_TABLE
**	------------
**	DESCRIPTION
**	Splits the command line by pipe lines
**	and adds them to the linked list of the command table.
**	PARAMETERS
**	#1. Pointer to struct data (data);
**	RETURN VALUES
**	-
*/
void	create_cmd_table(t_data *data)
{
	char	**pipe_line;
	int		i;

	i = 0;
	pipe_line = ft_split2(data->cmd_line, '|');
	while (pipe_line[i] != NULL)
	{
		cmd_lst_add_front(&data->head_cmd, pipe_line[i]);
		i++;
	}
	ft_matrix_free(pipe_line);
}
