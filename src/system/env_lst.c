/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 07:00:12 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/06/27 07:04:11 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ENV_LST_ADD_BACK
**	------------
**	DESCRIPTION
**	Add the node at the end of the circular linked list and change the last_env
**	pointer to the last node added.
**	PARAMETERS
**	#1. The pointer to list (last_env);
**	#2. The pointer to environment name (name);
**	#3. The pointer to environment value (value);
**	RETURN VALUES
**	Return 0 if successful and 1 if there is memory allocation error or if there
**	is no content in name and value
*/
int	env_lst_add_back(t_env **last_env, char *name, char *value)
{
	t_env	*new_node;

	if (!name || !value)
		return (EXIT_FAILURE);
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (EXIT_FAILURE);
	new_node->name = name;
	new_node->value = value;
	if ((*last_env) == NULL)
		new_node->next = new_node;
	else
	{
		new_node->next = (*last_env)->next;
		(*last_env)->next = new_node;
	}
	*last_env = new_node;
	return (EXIT_SUCCESS);
}

/*	FREE_ENV_LST
**	------------
**	DESCRIPTION
**	Free all memory allocated within environment circular linked list.
**	PARAMETERS
**	#1. The pointer to list (last_env);
**	RETURN VALUES
**	-
*/
void	free_env_lst(t_env **last_env)
{
	t_env	*temp;
	t_env	*current;

	if (*last_env == NULL)
		return ;
	current = (*last_env)->next;
	while (current != (*last_env))
	{
		free(current->name);
		free(current->value);
		temp = current->next;
		free(current);
		current = temp;
	}
	free((*last_env)->name);
	free((*last_env)->value);
	free((*last_env));
	*last_env = NULL;
}
