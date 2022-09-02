/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:04:34 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/02 14:01:04 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_first_node(t_env **head_env)
{
	t_env	*temp;

	free((*head_env)->name);
	free((*head_env)->value);
	temp = (*head_env)->next;
	free(*head_env);
	*head_env = temp;
}

void	del_node(t_env **env_list, char *word)
{
	t_env	*temp;
	t_env	*aux;

	temp = *env_list;
	while (temp != NULL && temp->next != NULL)
	{
		if (strcmp_eq(temp->next->name, word))
		{
			aux = temp->next;
			temp->next = aux->next;
			free(aux->name);
			free(aux->value);
			free(aux);
		}
		temp = temp->next;
	}
}

void	unset_env_var(t_env **env_list, char *word)
{
	if (strcmp_eq((*env_list)->name, word))
		del_first_node(env_list);
	else
		del_node(env_list, word);
}

void	builtin_unset(t_data *data, t_cmdtable *cmd_table)
{
	int		i;
	t_env	*temp;

	i = 1;
	while (cmd_table->word[i] != NULL)
	{
		unset_env_var(&data->head_env, cmd_table->word[i]);
		i++;
	}
}
