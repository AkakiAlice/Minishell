/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:07:51 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/09 21:44:21 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	IS_REDIRECT
**	------------
**	DESCRIPTION
**	Check if the string is redirect.
**	PARAMETERS
**	#1. String (cmd);
**	RETURN VALUES
**	Return true if the string is redirect and false if not
*/
bool	is_redirect(char *cmd)
{
	int	token;

	token = get_token(cmd);
	if (token == INPUT || token == HEREDOC || token == TRUNC || token == APPEND)
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
	count->redirect = 0;
}

/*	MALLOC_ARRAY_STR
**	------------
**	DESCRIPTION
**	Alloc memory from new array of string.
**	PARAMETERS
**	#1. Integer (count);
**	RETURN VALUES
**	Return allocated memory from new array of string.
*/
static char	**malloc_array_str(int count)
{
	char	**str;

	str = (char **)malloc(((sizeof(char *)) * (count + 1)));
	if (!str)
		return (NULL);
	return (str);
}

/*	INIT_CMD_VALUE
**	------------
**	DESCRIPTION
**	Initialize values from t_cmd_value struct and alloc memory.
**	PARAMETERS
**	#1. Pointer to struct cmd_value (cmd_value);
**	#2. Pointer to struct count (count);
**	RETURN VALUES
**	-
*/
void	init_cmd_value(t_cmd_value *cmd_value, t_counter *count)
{
	if (count->word > 0)
		cmd_value->word = malloc_array_str(count->word);
	else
		cmd_value->word = NULL;
	if (count->redirect > 0)
		cmd_value->redirect = malloc_array_str(count->redirect);
	else
		cmd_value->redirect = NULL;
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
