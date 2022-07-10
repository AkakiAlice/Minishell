/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 08:15:40 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/10 16:52:02 by pmitsuko         ###   ########.fr       */
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

/*	VALIDATE_VAR_NAME
**	------------
**	DESCRIPTION
**	Variable name validation. The name of variable can contain only letters
**	(a to z or A to Z), numbers (0 to 9) or the underscore character (_). The
**	first character cannot be a number.
**	PARAMETERS
**	#1. The pointers to variable name (var_name);
**	RETURN VALUES
**	Return 0 if variable name contains only allowed characters and 1 if it's
**	not.
*/
int	validate_var_name(char *var_name)
{
	int	i;

	i = 0;
	if (ft_isdigit(var_name[i]))
		return (FAILURE);
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

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

/*	VALIDATE_VAR_VALUE
**	------------
**	DESCRIPTION
**	Variable value validation. The value cannot contain space char ( ).
**	PARAMETERS
**	#1. The pointers to variable value (var_value);
**	RETURN VALUES
**	Return 0 if variable value contains only allowed characters and 1 if it's
**	not.
*/
int	validate_var_value(char *var_value)
{
	if (ft_strchr(var_value, ' ') == NULL)
		return (SUCCESS);
	return (FAILURE);
}

/*	IS_QUOTE
**	------------
**	DESCRIPTION
**	Check pointers contains simple quote or double quote and returns the first
**	occurrence of them.
**	PARAMETERS
**	#1. The pointers (str);
**	RETURN VALUES
**	Return 39 if the first occurrence is in single quotes, 34 for double quotes
**	and -1 if dont have quotes.
*/
int	is_quote(char *str)
{
	while (*str)
	{
		if (*str == S_QUOTE)
			return (S_QUOTE);
		if (*str == D_QUOTE)
			return (D_QUOTE);
		str++;
	}
	return (-1);
}

/*	COUNT_CHAR
**	------------
**	DESCRIPTION
**	Counts the number of characters (ch) that have been repeated in the string.
**	PARAMETERS
**	#1. The pointers (str);
**	#1. The character (ch);
**	RETURN VALUES
**	Returns repeat count.
*/
int	count_char(char *str, char ch)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ch)
			count++;
		str++;
	}
	return (count);
}

/*	REMOVE_SPACES_AROUND_STR
**	------------
**	DESCRIPTION
**	The space characters that are at the beginning and end of the string are
**	removed.
**	PARAMETERS
**	#1. The string (str);
**	RETURN VALUES
**	Return allocated memory from new string
*/
char	*remove_spaces_around_str(char *str)
{
	char	*new_str;
	int		str_len;

	if (!str)
		return (NULL);
	while(*str == ' ')
		str++;
	str_len = ft_strlen(str) - 1;
	while(str[str_len] == ' ')
		str_len--;
	new_str = ft_substr(str, 0, str_len + 1);
	return new_str;
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

	if (is_variable(cmd) == FAILURE)
		return (FAILURE);
	new_cmd = remove_spaces_around_str(cmd);
	if (new_cmd == NULL)
		return (FAILURE);
	split_cmd = ft_split(new_cmd, '=');
	if (split_cmd != NULL && split_cmd[0] != NULL)
	{
		var_value = get_var_value(new_cmd, split_cmd[0]);
		if (validate_var_name(split_cmd[0]) == FAILURE || validate_var_value(var_value) == FAILURE)
		{
			free(var_value);
			free(new_cmd);
			ft_matrix_free(split_cmd);
			return (FAILURE);
		}
		env_lst_add_back(last_var, ft_strdup(split_cmd[0]),
			ft_strdup(var_value));
	}
	free(var_value);
	free(new_cmd);
	ft_matrix_free(split_cmd);
	return (SUCCESS);
}
