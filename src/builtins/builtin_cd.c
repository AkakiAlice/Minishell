/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:54:06 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/08 12:25:12 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ERROR_MSG_CD
**	------------
**	DESCRIPTION
**	Prints on the screen the error message passed as an argument.
**	PARAMETERS
**	#1. The element to which the error message refers (str);
**	#2. The message that will be displayed (msg);
**	RETURN VALUES
**	-
*/
void	error_msg_cd(char *str, char *msg)
{
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	put_msg(str, msg, 2);
	g_data.status = 1;
}

/*	CHECK_IS_DIR_CD
**	------------
**	DESCRIPTION
**	Checks if the passed argument is a directory or not.
**	PARAMETERS
**	#1. Command table struct (cmd_table);
**	RETURN VALUES
**	Returns 1 if the argument passed is a directory, otherwise returns 0
*/
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

/*	CHANGE_DIR
**	------------
**	DESCRIPTION
**	Changes directory and set PWD and OLDPWD.
**	PARAMETERS
**	#1. The directory name (dir);
**	RETURN VALUES
**	-
*/
void	change_dir(char *dir)
{
	char	*new_pwd;
	char	cwd[1024];
	char	*old_pwd;
	char	old_cwd[1024];

	old_pwd = ft_strcat("OLDPWD=", getcwd(old_cwd, 1024));
	chdir(dir);
	new_pwd = ft_strcat("PWD=", getcwd(cwd, 1024));
	save_env_var(new_pwd, 1);
	save_env_var(old_pwd, 1);
	free(new_pwd);
	free(old_pwd);
}

/*	CHANGE_DIR_OLD_PWD
**	------------
**	DESCRIPTION
**	Changes directory to OLDPWD.
**	PARAMETERS
**	-
**	RETURN VALUES
**	-
*/
void	change_dir_old_pwd(void)
{
	char	*old_pwd;

	old_pwd = search_env_value("OLDPWD");
	if (old_pwd == NULL)
	{
		ft_putstr_fd("-minishell: cd: OLDPWD not set\n", 2);
		g_data.status = 1;
	}
	else
	{
		ft_printf("%s\n", old_pwd);
		change_dir(old_pwd);
	}
}

/*	BUILTIN_CD
**	------------
**	DESCRIPTION
**	Parses the input and call the directory change functions.
**	PARAMETERS
**	#1. Command table struct (cmd_table);
**	RETURN VALUES
**	-
*/
void	builtin_cd(t_cmdtable *cmd_table)
{
	if (cmd_table->word[1] && cmd_table->word[2])
	{
		ft_putstr_fd("-minishell: cd: too many arguments\n", 2);
		g_data.status = 1;
		return ;
	}
	if (strcmp_eq(cmd_table->word[1], "-"))
		change_dir_old_pwd();
	else if (cmd_table->word[1] == NULL || strcmp_eq(cmd_table->word[1], "~")
		|| strcmp_eq(cmd_table->word[1], "~/"))
		change_dir(getenv("HOME"));
	else if (check_is_dir_cd(cmd_table))
		change_dir(cmd_table->word[1]);
}
