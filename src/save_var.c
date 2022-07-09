/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 08:15:40 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/09 08:39:53 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	GET_VAR_VALUE
**	------------
**	DESCRIPTION
**	Get the variable value after the equal sign.
**	PARAMETERS
**	#1. The pointer to command (cmd);
**	#2. The pointer to variable name (var_name);
**	RETURN VALUES
**	Return allocated memory from variable value
*/
char	*get_var_value(char *cmd, char *var_name)
{
	int		name_len;
	int		value_len;
	char	*var_value;

	if (!cmd && !var_name)
		return (NULL);
	name_len = ft_strlen(var_name) + 1;
	value_len = ft_strlen(cmd + name_len);
	var_value = ft_substr(cmd, name_len, value_len);
	return (var_value);
}

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
		env_lst_add_back(last_var, ft_strdup(split_cmd[0]),
			get_var_value(cmd, split_cmd[0]));
	}
	ft_matrix_free(split_cmd);
	return ;
}
