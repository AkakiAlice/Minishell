/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:32:42 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/04 18:09:31 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	PUT_ENV
**	------------
**	DESCRIPTION
**	Prints all environment variables in the format: name=value
**	PARAMETERS
**	#1. The pointer to list "env" (head_env);
**	#2. The file descriptor (fd);
**	RETURN VALUES
**	-
*/
static void	put_env(t_env *head_env, int fd)
{
	while (head_env != NULL)
	{
		if (head_env->value)
		{
			ft_putstr_fd(head_env->name, fd);
			ft_putstr_fd("=", fd);
			ft_putendl_fd(head_env->value, fd);
		}
		head_env = head_env->next;
	}
}

/*	BUILTIN_ENV
**	------------
**	DESCRIPTION
**	Builtin env.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (head_table);
**	RETURN VALUES
**	-
*/
void	builtin_env(t_data *data, t_cmdtable *head_table)
{
	int	i;

	i = 1;
	if (head_table->word[i] && !is_equal_sign(head_table->word[i]))
	{
		free(data->cmd_path);
		no_such_file_exit(data, head_table->word[i], 127);
	}
	while (head_table->word[i])
	{
		if (*head_table->word[i] != '=')
			save_env_var(data, head_table->word[i], 0);
		else
			ft_putendl_fd(head_table->word[i], 1);
		i++;
	}
	put_env(data->head_env, 1);
}
