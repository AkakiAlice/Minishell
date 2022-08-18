/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:07:51 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/18 05:36:26 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	IS_LESS
**	------------
**	DESCRIPTION
**	Check if the string is less.
**	PARAMETERS
**	#1. String (cmd);
**	RETURN VALUES
**	Return true if the string is less and false if not
*/
bool	is_less(char *cmd)
{
	int	token;

	token = get_token(cmd);
	if (token == INPUT || token == HEREDOC)
		return (true);
	return (false);
}

/*	IS_GREAT
**	------------
**	DESCRIPTION
**	Check if the string is great.
**	PARAMETERS
**	#1. String (cmd);
**	RETURN VALUES
**	Return true if the string is great and false if not
*/
bool	is_great(char *cmd)
{
	int	token;

	token = get_token(cmd);
	if (token == TRUNC || token == APPEND)
		return (true);
	return (false);
}

/*	INIT_COUNT
**	------------
**	DESCRIPTION
**	Initialize values from t_counter struct.
**	PARAMETERS
**	#1. Pointer to struct count (count);
**	RETURN VALUES
**	-
*/
void	init_count(t_counter *count)
{
	count->word = 0;
	count->less = 0;
	count->great = 0;
}

/*	INIT_CMD_VALUE
**	------------
**	DESCRIPTION
**	Initialize values from t_cmd_value struct and alloc memory.
**	PARAMETERS
**	#1. Pointer to struct cmd_value (cmd_value);
**	#2. Pointer to struct count (count);
**	RETURN VALUES
**	Return 0 if success and 1 if error.
*/
int	init_cmd_value(t_cmd_value *cmd_value, t_counter *count)
{
	cmd_value->word = (char **)malloc(((sizeof(char *)) * (count->word + 1)));
	if (!cmd_value->word)
		return (FAILURE);
	cmd_value->less = (char **)malloc(((sizeof(char *)) * (count->less + 1)));
	if (!cmd_value->less)
		return (FAILURE);
	cmd_value->great = (char **)malloc(((sizeof(char *)) * (count->great + 1)));
	if (!cmd_value->great)
		return (FAILURE);
	return (SUCCESS);
}

/*	IS_VAR_EXPANSION
**	------------
**	DESCRIPTION
**	Check exists variable expansion in string.
**	PARAMETERS
**	#1. The string (str);
**	RETURN VALUES
**	Return true if contains variable expansion and false if its not.
*/
bool	is_var_expansion(char *str)
{
	while (*str)
	{
		if (*str == '$')
			return (true);
		str++;
	}
	return (false);
}
