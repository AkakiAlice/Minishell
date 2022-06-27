/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 18:45:46 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/06/27 07:00:20 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
