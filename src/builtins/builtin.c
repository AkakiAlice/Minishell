/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 06:11:32 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/03 16:06:02 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect_parent(t_cmdtable *head)
{
	if (!head->err_file)
		return (0);
	if (head->err_nb == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		put_msg(head->err_file, NO_FILE_DIR, 2);
		return (1);
	}
	if (head->err_nb == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		put_msg(head->err_file, INVALID_PERMISSION, 2);
		return (1);
	}
	return (0);
}

/*	EXEC_BUILTIN_PARENT
**	------------
**	DESCRIPTION
**	Execute the builtins in the parent process.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (head_table);
**	RETURN VALUES
**	-
*/
int	exec_builtin_parent(t_data *data, t_cmdtable *head_table)
{
	if (!head_table->word)
		return (1);
	if (strcmp_eq(*head_table->word, "exit"))
	{
		if (!data->is_pipe && !check_redirect_parent(head_table))
			builtin_exit(data, head_table);
		return (1);
	}
	if (strcmp_eq(*head_table->word, "export"))
	{
		if (!data->is_pipe && !check_redirect_parent(head_table))
			builtin_export(data, head_table);
		return (1);
	}
	if (strcmp_eq(*head_table->word, "unset"))
	{
		if (!data->is_pipe && !check_redirect_parent(head_table))
			builtin_unset(data, head_table);
		return (1);
	}
	return (0);
}

void	exec_builtin_child(t_data *data, char **word)
{
	if (strcmp_eq("echo", word[0]))
	{
		builtin_echo(word);
		free_minishell(data);
		free_env_lst(&data->head_env);
		free(data->cmd_path);
		exit(0);
	}
	if (strcmp_eq("pwd", word[0]))
	{
		builtin_pwd();
		free_minishell(data);
		free_env_lst(&data->head_env);
		free(data->cmd_path);
		exit(0);
	}
}
