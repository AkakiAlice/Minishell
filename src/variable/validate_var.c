/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 05:07:13 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/16 12:49:49 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	VALIDATE_VAR_NAME
**	------------
**	DESCRIPTION
**	Variable name validation. The name of variable can contain only letters
**	(a to z or A to Z), numbers (0 to 9) or the underscore character (_). The
**	first character cannot be a number.
**	PARAMETERS
**	#1. The pointers to variable name (var_name);
**	RETURN VALUES
**	Return true if variable name contains only allowed characters and false if
**	it's not.
*/
static bool	validate_var_name(char *var_name)
{
	int	i;

	i = 0;
	if (ft_isdigit(var_name[i]))
		return (false);
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/*	VALIDATE_VAR_VALUE
**	------------
**	DESCRIPTION
**	Variable value validation.
**	PARAMETERS
**	#1. The pointers to variable value (var_value);
**	RETURN VALUES
**	Return true if variable value contains only allowed characters and false if
**	it's not.
*/
static bool	validate_var_value(char *var_value)
{
	return (validate_quote_space(var_value));
}

/*	VALIDATE_VAR
**	------------
**	DESCRIPTION
**	Validates the name and value of the variable.
**	PARAMETERS
**	#1. The pointers to variable name (var_name);
**	#1. The pointers to variable value (var_value);
**	RETURN VALUES
**	Return true if variable contains only allowed characters and false if
**	it's not.
*/
bool	validate_var(char *var_name, char *var_value)
{
	if (validate_var_name(var_name) && validate_var_value(var_value))
		return (true);
	return (false);
}
