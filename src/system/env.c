/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 18:45:46 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/06/23 05:39:57 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_lst_add_back(t_env **env_last)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (EXIT_FAILURE);
	new_node->name = NULL;
	new_node->value = NULL;
	if ((*env_last) == NULL)
		new_node->next = new_node;
	else
	{
		new_node->next = (*env_last)->next;
		(*env_last)->next = new_node;
	}
	*env_last = new_node;
	return (EXIT_SUCCESS);
}

void	save_env(t_env **env, char **envp)
{
	int		i;
	char	**split_env;

	i = 0;
	while (envp[i])
	{
		split_env = ft_split(envp[i], '=');
		if (split_env[0] != NULL)
		{
			if (env_lst_add_back(env) == EXIT_SUCCESS)
			{
				(*env)->name = ft_strdup(split_env[0]);
			}
		}
		ft_matrix_free(split_env);
		i++;
	}
	return ;
}
