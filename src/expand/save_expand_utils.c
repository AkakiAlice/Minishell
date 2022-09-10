/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_expand_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:16:18 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/10 17:36:12 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	SAVE_STR
**	------------
**	DESCRIPTION
**	Concatenate string and include space after the string.
**	PARAMETERS
**	#1. The result string (result);
**	#2. The string (str);
**	#3. The flag to include space at the end (space);
**	RETURN VALUES
**	-
*/
void	save_str(char **result, char *str, bool space)
{
	if (*result != NULL)
		strcat_space(result, str, space);
	else
	{
		if (space)
			*result = ft_strcat(str, " ");
		else
			*result = ft_strdup(str);
	}
}

/*	SAVE_PREFIX
**	------------
**	DESCRIPTION
**	Save prefix expand.
**	PARAMETERS
**	#1. The result string (result);
**	#2. The string (str);
**	#3. The size to be saved (diff);
**	RETURN VALUES
**	-
*/
void	save_prefix(char **result, char *str, int diff)
{
	char	*prefix;
	char	*temp_result;

	if (*result)
	{
		prefix = ft_substr(str, 0, diff);
		temp_result = ft_strdup(*result);
		free(*result);
		*result = ft_strcat(temp_result, prefix);
		free(prefix);
		free(temp_result);
	}
	else
		*result = ft_substr(str, 0, diff);
}

/*	SAVE_EXIT_CODE_SUFFIX
**	------------
**	DESCRIPTION
**	Save exit code with suffix.
**	PARAMETERS
**	#1. The result string (result);
**	#2. The string (str);
**	#3. The exit code (exit);
**	#4. The flag to include space at the end (spc);
**	RETURN VALUES
**	-
*/
void	save_exit_code_suffix(char **result, char *str, char *exit, bool spc)
{
	char	*suffix;
	char	*aux;

	suffix = ft_substr(str, 2, ft_strlen(str) - 2);
	if (*result)
	{
		aux = ft_strcat(exit, suffix);
		strcat_space(result, aux, spc);
		free(aux);
	}
	else
	{
		*result = ft_strcat(exit, suffix);
		if (spc)
			add_space(result);
	}
	free(suffix);
}

/*	SAVE_EXIT_CODE
**	------------
**	DESCRIPTION
**	Save exit code.
**	PARAMETERS
**	#1. The result string (result);
**	#2. The string (str);
**	#3. The flag to include space at the end (spc);
**	RETURN VALUES
**	-
*/
void	save_exit_code(char **result, char *str, bool space)
{
	char	*exit_code;

	exit_code = ft_itoa(g_data.status);
	if (ft_strlen(str) > 2)
		save_exit_code_suffix(result, str, exit_code, space);
	else
	{
		if (*result)
			strcat_space(result, exit_code, space);
		else
		{
			*result = ft_itoa(g_data.status);
			if (space)
				add_space(result);
		}
	}
	free(exit_code);
}

/*	SAVE_EXPAND_VALUE
**	------------
**	DESCRIPTION
**	Save expand value.
**	PARAMETERS
**	#1. The result string (result);
**	#2. The string (str);
**	#3. The flag to include space at the end (spc);
**	RETURN VALUES
**	-
*/
void	save_expand_env(char **result, char *str, bool space)
{
	char	*env_value;

	env_value = expand_env(str);
	if (*result)
	{
		if (env_value != NULL)
			strcat_space(result, env_value, space);
	}
	else
	{
		if (env_value == NULL)
			*result = ft_strdup("");
		else
			*result = ft_strdup(env_value);
		if (space)
			add_space(result);
	}
}
