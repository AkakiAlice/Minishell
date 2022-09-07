/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:54:06 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/07 14:33:06 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg_cd(char *str, char *msg)
{
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	put_msg(str, msg, 2);
	g_data.status = 1;
}

int	check_is_dir_cd(t_cmdtable *cmd_table)
{
	DIR	*dir;

	dir = opendir(cmd_table->word[1]);
	if (!dir && access(cmd_table->word[1], F_OK) == -1)
	{
		error_msg_cd(cmd_table->word[1], NO_FILE_DIR);
		return (0);
	}
	if (access(cmd_table->word[1], F_OK) == 0 && !dir)
	{
		error_msg_cd(cmd_table->word[1], NO_DIR);
		return (0);
	}
	closedir(dir);
	return (1);
}

void	change_dir(t_data *data, char *dir)
{
	char	*new_pwd;
	char	cwd[1024];
	char	*old_pwd;
	char	old_cwd[1024];

	old_pwd = ft_strcat("OLDPWD=", getcwd(old_cwd, 1024));
	chdir(dir);
	new_pwd = ft_strcat("PWD=", getcwd(cwd, 1024));
	save_env_var(data, new_pwd, 1);
	save_env_var(data, old_pwd, 1);
	free(new_pwd);
	free(old_pwd);
}

void	change_dir_old_pwd(t_data *data)
{
	char	*old_pwd;

	old_pwd = get_var_value_expand(data->head_env, "OLDPWD");
	if (old_pwd == NULL)
	{
		ft_putstr_fd("-minishell: cd: OLDPWD not set\n", 2);
		g_data.status = 1;
	}
	else
	{
		ft_printf("%s\n", old_pwd);
		change_dir(data, old_pwd);
	}
}

void	builtin_cd(t_data *data, t_cmdtable *cmd_table)
{
	if (cmd_table->word[1] && cmd_table->word[2])
	{
		ft_putstr_fd("-minishell: cd: too many arguments\n", 2);
		g_data.status = 1;
		return ;
	}
	if (strcmp_eq(cmd_table->word[1], "-"))
		change_dir_old_pwd(data);
	else if (cmd_table->word[1] == NULL || strcmp_eq(cmd_table->word[1], "~")
		|| strcmp_eq(cmd_table->word[1], "~/"))
		change_dir(data, getenv("HOME"));
	else if (check_is_dir_cd(cmd_table))
		change_dir(data, cmd_table->word[1]);
}
