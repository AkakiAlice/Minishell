/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 05:00:04 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/07 18:50:23 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	IS_EQUAL_SIGN
**	------------
**	DESCRIPTION
**	Check the command line is a variable declaration.
**	PARAMETERS
**	#1. The pointers to command line (cmd);
**	RETURN VALUES
**	Return true if command line is variable declaration and false if it's not.
*/
bool	is_equal_sign(char *cmd)
{
	if (ft_strchr(cmd, '=') == NULL)
		return (false);
	return (true);
}
