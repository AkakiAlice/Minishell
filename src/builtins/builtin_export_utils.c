/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:34:29 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/09 08:56:39 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	PUT_EXPORT
**	------------
**	DESCRIPTION
**	Prints all environment variables in the format: declare -x name="value"
**	PARAMETERS
**	#1. The file descriptor (fd);
**	RETURN VALUES
**	-
*/
void	put_export(int fd)
{
	t_env	*head_env;

	head_env = g_data.head_env;
	while (head_env != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(head_env->name, fd);
		if (head_env->value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(head_env->value, fd);
			ft_putendl_fd("\"", fd);
		}
		else
			ft_putstr_fd("\n", fd);
		head_env = head_env->next;
	}
}

/*	PUT_MSG_BUILTIN
**	------------
**	DESCRIPTION
**	Prints message in the format minishell: builtin: eof: message
**	PARAMETERS
**	#1. The builtin (builtin);
**	#2. The eof (eof);
**	#3. The message (msg);
**	#4. The file descriptor (fd);
**	RETURN VALUES
**	-
*/
static void	put_msg_builtin(char *builtin, char *eof, char *msg, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(builtin, fd);
	ft_putstr_fd(": `", fd);
	ft_putstr_fd(eof, fd);
	ft_putstr_fd("': ", fd);
	ft_putendl_fd(msg, fd);
	return ;
}

/*	EXPORT_ERROR
**	------------
**	DESCRIPTION
**	Print invalid id error message and change exit code value.
**	PARAMETERS
**	#1. The string (variable);
**	RETURN VALUES
**	Return 0.
*/
int	export_error(char *variable)
{
	put_msg_builtin("export", variable, NOT_VALID_ID, 2);
	return (0);
}
