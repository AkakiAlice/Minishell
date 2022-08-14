/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 08:13:46 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/14 18:10:51 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	TOKEN_LST_ADD_BACK
**	------------
**	DESCRIPTION
**	Add the node at the end of the linked list and change the
**	head_token pointer to the last node added.
**	PARAMETERS
**	#1. The pointer to list (head_token);
**	#2. The pointer to token value (value);
**	RETURN VALUES
**	Return 0 if successful and 1 if there is memory allocation error
*/
int	token_lst_add_back(t_token **head_token, int value)
{
	t_token	*new_node;
	t_token	*temp;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (EXIT_FAILURE);
	new_node->value = value;
	new_node->next = NULL;
	if ((*head_token) == NULL)
		*head_token = new_node;
	else
	{
		temp = *head_token;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	return (EXIT_SUCCESS);
}

/*	FREE_TOKEN_LST
**	------------
**	DESCRIPTION
**	Free all memory allocated within token linked list.
**	PARAMETERS
**	#1. The pointer to last element list (head_token);
**	RETURN VALUES
**	-
*/
void	free_token_lst(t_token **head_token)
{
	t_token	*temp;

	if (*head_token == NULL)
		return ;
	while (*head_token != NULL)
	{
		temp = (*head_token)->next;
		free(*head_token);
		*head_token = temp;
	}
	*head_token = NULL;
}
