/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 05:28:09 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/09 08:56:17 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	CHANGE_ENV_VAR
**	------------
**	DESCRIPTION
**	Check if the env variable exists and change value.
**	PARAMETERS
**	#1. The string (var_name);
**	#2. The string (var_value);
**	RETURN VALUES
**	Return 1 if env exists and 0 if not.
*/
static int	change_env_var(char *var_name, char *var_value)
{
	t_env	*head_env;

	head_env = g_data.head_env;
	while (head_env != NULL)
	{
		if (strcmp_eq(head_env->name, var_name))
		{
			if (head_env->value)
				free(head_env->value);
			head_env->value = var_value;
			return (1);
		}
		head_env = head_env->next;
	}
	return (0);
}

/*	ENV_VAR_EXISTS
**	------------
**	DESCRIPTION
**	Check if the env variable exists.
**	PARAMETERS
**	#1. The string (var_name);
**	RETURN VALUES
**	Return 1 if env exists and 0 if not.
*/
static int	env_var_exists(char *var_name)
{
	t_env	*head_env;

	head_env = g_data.head_env;
	while (head_env != NULL)
	{
		if (strcmp_eq(head_env->name, var_name))
			return (1);
		head_env = head_env->next;
	}
	return (0);
}

/*	SAVE_ONLY_NAME
**	------------
**	DESCRIPTION
**	Save the env name in the linked list.
**	PARAMETERS
**	#1. The string (variable);
**	RETURN VALUES
**	Return 1 if success and 0 if failure.
*/
static int	save_only_name(char *variable)
{
	if (env_var_exists(variable))
		return (1);
	if (validate_var_name(variable))
	{
		env_lst_add_back(&g_data.head_env, ft_strdup(variable), NULL);
		return (1);
	}
	return (export_error(variable));
}

/*	SAVE_ENV_VAR
**	------------
**	DESCRIPTION
**	Validate the variable assignment and save the env variable in the linked
**	list.
**	PARAMETERS
**	#1. The variable (variable);
**	#2. The flag validate variable (validate);
**	RETURN VALUES
**	Return 1 if success and 0 if failure.
*/
int	save_env_var(char *variable, int validate)
{
	char	**split_var;
	char	*env_value;

	if (validate && *variable == '=')
		return (export_error(variable));
	if (!is_equal_sign(variable))
		return (save_only_name(variable));
	split_var = ft_split(variable, '=');
	if (split_var == NULL)
		return (0);
	if (validate && !validate_var_name(split_var[0]))
	{
		ft_matrix_free(&split_var);
		return (export_error(variable));
	}
	env_value = get_env_value(variable, split_var[0]);
	if (!change_env_var(split_var[0], env_value))
		env_lst_add_back(&g_data.head_env, ft_strdup(split_var[0]), env_value);
	ft_matrix_free(&split_var);
	return (1);
}

/*	BUILTIN_EXPORT
**	------------
**	DESCRIPTION
**	Builtin export.
**	PARAMETERS
**	#1. The pointer to list (head_table);
**	RETURN VALUES
**	-
*/
void	builtin_export(t_cmdtable *head_table)
{
	int		i;
	int		result;
	bool	error;

	i = 1;
	error = false;
	if (head_table->word[i] == NULL)
		return (put_export(head_table->fdout));
	while (head_table->word[i])
	{
		result = save_env_var(head_table->word[i], 1);
		if (!error && !result)
			error = true;
		i++;
	}
	if (error)
		g_data.status = 1;
	else
		g_data.status = 0;
}
