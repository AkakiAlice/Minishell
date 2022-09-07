/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 06:11:32 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/07 17:46:04 by alida-si         ###   ########.fr       */
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
int	exec_builtin_parent(t_cmdtable *head_table, int builtin)
{
	if (g_data.is_pipe || check_redirect_parent(head_table))
		return (1);
	if (builtin == EXIT)
		builtin_exit(head_table);
	else if (builtin == EXPORT)
		builtin_export(head_table);
	else if (builtin == UNSET)
		builtin_unset(head_table);
	else if (builtin == CD)
		builtin_cd(head_table);
	return (1);
}

int	check_builtin(t_cmdtable *cmd_table)
{
	if (!cmd_table->word)
		return (1);
	if (strcmp_eq(*cmd_table->word, "exit"))
		return (exec_builtin_parent(cmd_table, EXIT));
	if (strcmp_eq(*cmd_table->word, "export"))
		return (exec_builtin_parent(cmd_table, EXPORT));
	if (strcmp_eq(*cmd_table->word, "unset"))
		return (exec_builtin_parent(cmd_table, UNSET));
	if (strcmp_eq(*cmd_table->word, "cd"))
		return (exec_builtin_parent(cmd_table, CD));
	return (0);
}

void	exit_builtin_child()
{
	clear_minishell();
	free(g_data.cmd_path);
	exit(0);
}

void	exec_builtin_child(t_cmdtable *head_table)
{
	if (strcmp_eq("echo", head_table->word[0]))
	{
		builtin_echo(head_table->word);
		exit_builtin_child();
	}
	if (strcmp_eq("pwd", head_table->word[0]))
	{
		builtin_pwd();
		exit_builtin_child();
	}
	if (strcmp_eq("env", head_table->word[0]))
	{
		builtin_env(head_table);
		exit_builtin_child();
	}
}
