/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 05:00:04 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/12 05:32:32 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	IS_VARIABLE
**	------------
**	DESCRIPTION
**	Check the command line is a variable declaration.
**	PARAMETERS
**	#1. The pointers to command line (cmd);
**	RETURN VALUES
**	Return 0 if command line is variable declaration and 1 if it's not.
*/
int	is_variable(char *cmd)
{
	if (ft_strchr(cmd, '=') == NULL)
		return (FAILURE);
	return (SUCCESS);
}

/*	FREE_VARIABLE
**	------------
**	DESCRIPTION
**	Free all memory allocated in function save_var.
**	PARAMETERS
**	#1. The pointers to string variable value (var_value);
**	#2. The pointers to string command (cmd);
**	#3. The pointers to array of strings (split);
**	#4. The status (status);
**	RETURN VALUES
**	Return status.
*/
int	free_variable(char **var_value, char **cmd, char ***split, int status)
{
	if (*var_value != NULL)
		free(*var_value);
	if (*cmd != NULL)
		free(*cmd);
	if (*split != NULL)
		ft_matrix_free(*split);
	return (status);
}
