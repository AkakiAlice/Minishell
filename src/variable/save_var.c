/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 08:15:40 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/16 13:01:24 by pmitsuko         ###   ########.fr       */
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
int	save_var(t_env **last_var, char *cmd)
{
	char	**split_cmd;
	char	*var_value;
	char	*new_cmd;

	if (!is_variable(cmd))
		return (FAILURE);
	new_cmd = remove_spaces_around_str(cmd);
	if (new_cmd == NULL)
		return (FAILURE);
	split_cmd = ft_split(new_cmd, '=');
	if (split_cmd != NULL && split_cmd[0] != NULL)
	{
		var_value = get_var_value(new_cmd, split_cmd[0]);
		if (!validate_var(split_cmd[0], var_value))
			return (free_variable(&var_value, &new_cmd, &split_cmd, FAILURE));
		env_lst_add_back(last_var, ft_strdup(split_cmd[0]),
			str_without_quotes(var_value));
	}
	return (free_variable(&var_value, &new_cmd, &split_cmd, SUCCESS));
}
