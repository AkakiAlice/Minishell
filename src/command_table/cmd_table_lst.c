/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:05:41 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/18 05:57:37 by pmitsuko         ###   ########.fr       */
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

// ! Função temporária
void	cmdlst_printf(t_cmdtable *cmd)
{
	int	i;

	i = 0;
	while (cmd != NULL)
	{
		ft_printf("List: [%d]\n", i++);
		cmd = cmd->next;
	}
	return ;
}

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
		ft_matrix_free(&(*head_cmd)->word);
		ft_matrix_free(&(*head_cmd)->less);
		ft_matrix_free(&(*head_cmd)->great);
		temp = (*head_cmd)->next;
		free(*head_cmd);
		*head_cmd = temp;
	}
	*head_cmd = NULL;
}

/*	CMD_LST_ADD_FRONT
**	------------
**	DESCRIPTION
**	Add the new node at the end of the singly linked list.
**	PARAMETERS
**	#1. The pointer to list (head_cmd);
**	#2. The word array (word);
**	RETURN VALUES
**	-
*/
void	cmd_lst_add_front(t_cmdtable **head_cmd, t_cmd_value cmd_v)
{
	t_cmdtable	*ptr;
	t_cmdtable	*temp;

	ptr = (t_cmdtable *)malloc(sizeof(t_cmdtable));
	if (!ptr)
		return ;
	ptr->word = cmd_v.word;
	ptr->less = cmd_v.less;
	ptr->great = cmd_v.great;
	if ((*head_cmd) == NULL)
	{
		ptr->next = NULL;
		*head_cmd = ptr;
	}
	else
	{
		temp = *head_cmd;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = ptr;
		ptr->next = NULL;
	}
}
