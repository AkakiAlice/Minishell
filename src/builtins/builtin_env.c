/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:32:42 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/03 17:08:13 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_env(t_env *head_env, int fd)
{
	while (head_env != NULL)
	{
		if (head_env->value)
		{
			ft_putstr_fd(head_env->name, fd);
			ft_putstr_fd("=", fd);
			ft_putendl_fd(head_env->value, fd);
		}
		else
			ft_putstr_fd("\n", fd);
		head_env = head_env->next;
	}
}

void	builtin_env(t_data *data, t_cmdtable *head_table)
{
	(void)head_table;
	put_env(data->head_env, 1);
}
