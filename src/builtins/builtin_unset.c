/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:04:34 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/07 17:17:15 by alida-si         ###   ########.fr       */
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

int	valid_unset_var(char *word)
{
	int	i;

	i = 0;
	if (ft_isalpha(word[i]) != 0 || word[i] == '_')
	{
		while (word[i] != '\0')
		{
			if (ft_isalnum(word[i]) == 0 && word[i] != '_')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
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
		if (valid_unset_var(cmd_table->word[i]))
			unset_env_var(&g_data.head_env, cmd_table->word[i]);
		else
			unset_error_msg(cmd_table->word[i]);
		i++;
	}
}
