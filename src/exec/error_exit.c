/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:34:22 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/08 14:02:28 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	IS_DIR_EXIT
**	------------
**	DESCRIPTION
**	Displays the error message "Is a directory" and terminates the process.
**	PARAMETERS
**	#1. The element to which the error message refers (word);
**	RETURN VALUES
**	-
*/
void	is_dir_exit(char *word)
{
	ft_putstr_fd("minishell: ", 2);
	put_msg(word, IS_DIR, 2);
	free_minishell();
	free_env_lst(&g_data.head_env);
	exit(126);
}

/*	NO_SUCH_FILE_EXIT
**	------------
**	DESCRIPTION
**	Displays the error message "No such file or directory"
**	and terminates the process.
**	PARAMETERS
**	#1. The element to which the error message refers (word);
**	#2. The status that the process must be terminated (status);
**	RETURN VALUES
**	-
*/
void	no_such_file_exit(char *word, int status)
{
	ft_putstr_fd("minishell: ", 2);
	put_msg(word, NO_FILE_DIR, 2);
	free_minishell();
	free_env_lst(&g_data.head_env);
	free(g_data.cmd_path);
	exit(status);
}

/*	INVALID_PERMISSION_EXIT
**	------------
**	DESCRIPTION
**	Displays the error message "Permission denied" and terminates the process.
**	PARAMETERS
**	#1. The element to which the error message refers (word);
**	#2. The status that the process must be terminated (status);
**	RETURN VALUES
**	-
*/
void	invalid_permission_exit(char *word, int status)
{
	ft_putstr_fd("minishell: ", 2);
	put_msg(word, INVALID_PERMISSION, 2);
	free_minishell();
	free_env_lst(&g_data.head_env);
	exit(status);
}
