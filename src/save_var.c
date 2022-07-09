/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 08:15:40 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/09 08:31:29 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	SAVE_VAR
**	------------
**	DESCRIPTION
**	Save variables in circular linked list.
**	PARAMETERS
**	#1. The last node of the circular linked list (last_var);
**	#2. The pointers to command line (cmd);
**	RETURN VALUES
**	-
*/
void	save_var(t_env **last_var, char *cmd)
{
	char	**split_cmd;

	split_cmd = ft_split(cmd, '=');
	if (split_cmd != NULL && split_cmd[0] != NULL)
	{
		env_lst_add_back(last_var, ft_strdup(split_cmd[0]), ft_strdup(" "));
	}
	ft_matrix_free(split_cmd);

	// i = 0;
	// while (last_var[i])
	// {
	// 	split_env = ft_split(envp[i], '=');
	// 	if (split_env[0] != NULL)
	// 	{
	// 		env_lst_add_back(env, ft_strdup(split_env[0]),
	// 			get_env_value(envp[i], split_env[0]));
	// 	}
	// 	ft_matrix_free(split_env);
	// 	i++;
	// }
	return ;
}
