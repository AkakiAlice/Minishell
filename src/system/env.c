/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 18:45:46 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/06/25 07:49:51 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ENV_LST_ADD_BACK
**	------------
**	DESCRIPTION
**	Add the node at the end of the circular linked list and change the env_last
**	pointer to the last node added.
**	PARAMETERS
**	#1. The pointer to list (env_last);
**	#2. The pointer to environment name (name);
**	#3. The pointer to environment value (value);
**	RETURN VALUES
**	Return 0 if successful and 1 if there is memory allocation error or if there
**	is no content in name and value
*/
int	env_lst_add_back(t_env **env_last, char *name, char *value)
{
	t_env	*new_node;

	if (!name || !value)
		return (EXIT_FAILURE);
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (EXIT_FAILURE);
	new_node->name = name;
	new_node->value = value;
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

/*	GET_ENV_VALUE
**	------------
**	DESCRIPTION
**	Get the environment value after the equal sign.
**	PARAMETERS
**	#1. The pointer to environment variable (envp);
**	#2. The pointer to environment name (env_name);
**	RETURN VALUES
**	Return allocated memory from environment value
*/
char	*get_env_value(char *envp, char *env_name)
{
	int		key_len;
	int		value_len;
	char	*env_value;

	if (!envp && !env_name)
		return (NULL);
	key_len = ft_strlen(env_name) + 1;
	value_len = ft_strlen(envp + key_len);
	env_value = ft_substr(envp, key_len, value_len);
	return (env_value);
}

/*	SAVE_ENV
**	------------
**	DESCRIPTION
**	Save environment variables in circular linked list.
**	PARAMETERS
**	#1. The last node of the circular linked list (env);
**	#2. The array of pointers to environment variables (envp);
**	RETURN VALUES
**	-
*/
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
			env_lst_add_back(env, ft_strdup(split_env[0]),
				get_env_value(envp[i], split_env[0]));
		}
		ft_matrix_free(split_env);
		i++;
	}
	return ;
}
