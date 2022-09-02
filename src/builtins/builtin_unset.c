/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:04:34 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/02 02:18:38 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_node(t_env **env_list, char *word)
{

	t_env	*temp;
	t_env	*aux;

	temp = *env_list;
	aux = NULL;
	if (strcmp_eq(temp->name, word))
	{
		aux = temp;
		temp = temp->next;
		//env_list = temp->next;
	}
	if (aux)
	{
		//free(aux->name);
		//free(aux->value);
		free(aux);
	}
	/*while (temp->next != NULL)
	{
		//if (strcmp_eq(temp->name, word))
		//{
			ft_printf("> %s\n", temp->name);
	//	}
		temp = temp->next;
	}*/
	(void)word;
}

void	builtin_unset(t_data *data, t_cmdtable *cmd_table)
{
	int	i;
	t_env *temp = data->head_env;

	i = 1;
	while (cmd_table->word[i] != NULL)
	{
		del_node(&data->head_env, cmd_table->word[i]);
		i++;
	}
	while (temp != NULL)
	{
		ft_printf("> %s\n", temp->name);
		temp = temp->next;
	}
	(void)data;
}