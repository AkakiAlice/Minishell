/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 07:00:12 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/03 08:02:01 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ENV_LST_ADD_BACK
**	------------
**	DESCRIPTION
**	Add the node at the end of the circular linked list and change the head_env
**	pointer to the last node added.
**	PARAMETERS
**	#1. The pointer to list (head_env);
**	#2. The pointer to environment name (name);
**	#3. The pointer to environment value (value);
**	RETURN VALUES
**	Return 0 if successful and 1 if there is memory allocation error or if there
**	is no content in name and value
*/
int	env_lst_add_back(t_env **head_env, char *name, char *value)
{
	t_env	*new_node;
	t_env	*temp;

	if (!name)
		return (EXIT_FAILURE);
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (EXIT_FAILURE);
	new_node->name = name;
	new_node->value = value;
	new_node->next = NULL;
	if ((*head_env) == NULL)
		*head_env = new_node;
	else
	{
		temp = *head_env;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	return (EXIT_SUCCESS);
}

/*	FREE_ENV_LST
**	------------
**	DESCRIPTION
**	Free all memory allocated within environment circular linked list.
**	PARAMETERS
**	#1. The pointer to list (head_env);
**	RETURN VALUES
**	-
*/
void	free_env_lst(t_env **head_env)
{
	t_env	*temp;

	if (*head_env == NULL)
		return ;
	while (*head_env != NULL)
	{
		free((*head_env)->name);
		free((*head_env)->value);
		temp = (*head_env)->next;
		free(*head_env);
		*head_env = temp;
	}
	*head_env = NULL;
}
