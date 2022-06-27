/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:50:31 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/06/27 07:52:12 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	TOKEN_LST_ADD_BACK
**	------------
**	DESCRIPTION
**	Add the node at the end of the circular linked list and change the
**	last_token pointer to the last node added.
**	PARAMETERS
**	#1. The pointer to list (last_token);
**	#3. The pointer to token value (value);
**	RETURN VALUES
**	Return 0 if successful and 1 if there is memory allocation error
*/
int	token_lst_add_back(t_token **last_token, int value)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (EXIT_FAILURE);
	new_node->value = value;
	if ((*last_token) == NULL)
		new_node->next = new_node;
	else
	{
		new_node->next = (*last_token)->next;
		(*last_token)->next = new_node;
	}
	*last_token = new_node;
	return (EXIT_SUCCESS);
}

/*	FREE_TOKEN_LST
**	------------
**	DESCRIPTION
**	Free all memory allocated within token circular linked list.
**	PARAMETERS
**	#1. The pointer to last element list (last_token);
**	RETURN VALUES
**	-
*/
void	free_token_lst(t_token **last_token)
{
	t_token	*temp;
	t_token	*current;

	if (*last_token == NULL)
		return ;
	current = (*last_token)->next;
	while (current != (*last_token))
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	free((*last_token));
	*last_token = NULL;
}


void	lexer(t_token **last_token, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '|') != NULL)
			token_lst_add_back(last_token, PIPE);
		i++;
	}
	return ;
}
