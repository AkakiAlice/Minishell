/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:04:34 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/07 18:57:05 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env_var(t_env **env_list, char *word)
{
	if (strcmp_eq((*env_list)->name, word))
		del_first_node(env_list);
	else
		del_node(env_list, word);
}

void	unset_error_msg(char *word)
{
	ft_putstr_fd("-minishell: unset: `", 2);
	ft_putstr_fd(word, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	g_data.status = 1;
}

void	builtin_unset(t_cmdtable *cmd_table)
{
	int		i;

	i = 1;
	while (cmd_table->word[i] != NULL)
	{
		if (validate_var_name(cmd_table->word[i]))
			unset_env_var(&g_data.head_env, cmd_table->word[i]);
		else
			unset_error_msg(cmd_table->word[i]);
		i++;
	}
}
