/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 05:28:09 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/04 18:03:37 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	CHANGE_ENV_VAR
**	------------
**	DESCRIPTION
**	Check if the env variable exists and change value.
**	PARAMETERS
**	#1. The pointer to list "env" (head_env);
**	#2. The string (var_name);
**	#2. The string (var_value);
**	RETURN VALUES
**	Return 1 if env exists and 0 if not.
*/
static int	change_env_var(t_env *head_env, char *var_name, char *var_value)
{
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
**	#1. The pointer to list "env" (head_env);
**	#2. The string (variable_name);
**	RETURN VALUES
**	Return 1 if env exists and 0 if not.
*/
static int	env_var_exists(t_env *head_env, char *var_name)
{
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
**	#1. The pointer to struct "data" (data);
**	#2. The string (variable);
**	RETURN VALUES
**	-
*/
static void	save_only_name(t_data *data, char *variable)
{
	if (env_var_exists(data->head_env, variable))
		return ;
	if (validate_var_name(variable))
	{
		env_lst_add_back(&data->head_env, ft_strdup(variable), NULL);
		data->status = 0;
	}
	else
		export_error(data, variable);
}

/*	SAVE_ENV_VAR
**	------------
**	DESCRIPTION
**	Validate the variable assignment and save the env variable in the linked
**	list.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The variable (variable);
**	#3. The flag validate variable (validate);
**	RETURN VALUES
**	-
*/
void	save_env_var(t_data *data, char *variable, int validate)
{
	char	**split_var;
	char	*env_value;

	if (validate && *variable == '=')
		return (export_error(data, variable));
	if (!is_equal_sign(variable))
		return (save_only_name(data, variable));
	split_var = ft_split(variable, '=');
	if (split_var == NULL)
		return ;
	if (validate && !validate_var_name(split_var[0]))
	{
		ft_matrix_free(&split_var);
		return (export_error(data, variable));
	}
	env_value = get_env_value(variable, split_var[0]);
	if (!change_env_var(data->head_env, split_var[0], env_value))
		env_lst_add_back(&data->head_env, ft_strdup(split_var[0]), env_value);
	data->status = 0;
	ft_matrix_free(&split_var);
}

/*	BUILTIN_EXPORT
**	------------
**	DESCRIPTION
**	Builtin export.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (head_table);
**	RETURN VALUES
**	-
*/
void	builtin_export(t_data *data, t_cmdtable *head_table)
{
	int	i;

	i = 1;
	if (head_table->word[i] == NULL)
	{
		put_export(data->head_env, head_table->fdout);
		data->status = 0;
		return ;
	}
	while (head_table->word[i])
	{
		save_env_var(data, head_table->word[i], 1);
		i++;
	}
}
