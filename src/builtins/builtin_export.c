/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 05:28:09 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/03 07:34:22 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_env(t_env *head_env)
{
	while (head_env != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(head_env->name, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(head_env->value, 1);
		ft_putendl_fd("\"", 1);
		head_env = head_env->next;
	}
}

int	change_env_var(t_env *head_env, char *var_name, char *var_value)
{
	while (head_env != NULL)
	{
		if (strcmp_eq(head_env->name, var_name))
		{
			free(head_env->value);
			head_env->value = var_value;
			return (1);
		}
		head_env = head_env->next;
	}
	return (0);
}

void	save_env_var(t_data *data, char *variable)
{
	char	**split_var;
	char	*env_value;

	if (!is_variable(variable))
		return ;
	split_var = ft_split(variable, '=');
	if (split_var == NULL)
		return;
	env_value = get_env_value(variable, split_var[0]);
	if (!change_env_var(data->head_env, split_var[0], env_value)) {
		env_lst_add_back(&data->head_env, ft_strdup(split_var[0]), env_value);
	}
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
	if (head_table->word[1] == NULL)
	{
		put_env(data->head_env);
		return ;
	}
	save_env_var(data, head_table->word[1]);
}
