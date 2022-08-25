/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:06:33 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/25 07:12:56 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	PUT_MSG
**	------------
**	DESCRIPTION
**	Put message in 'title: description' format.
**	PARAMETERS
**	#1. The output title (title);
**	#2. The output message (msg);
**	#3. The file descriptor (fd);
**	RETURN VALUES
**	-
*/
void	put_msg(char *title, char *msg, int fd)
{
	ft_putstr_fd(title, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(msg, fd);
	return ;
}

/*	PUT_MSG_CMD
**	------------
**	DESCRIPTION
**	Put message in 'title: cmd: description' format.
**	PARAMETERS
**	#1. The output title (title);
**	#1. The output cmd (cmd);
**	#2. The output description (msg);
**	#3. The file descriptor (fd);
**	RETURN VALUES
**	-
*/
void	put_msg_cmd(char *title, char *cmd, char *msg, int fd)
{
	ft_putstr_fd(title, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(msg, fd);
	return ;
}
