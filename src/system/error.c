/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 06:57:58 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/08 07:52:44 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ERROR_MSG_EXIT
**	------------
**	DESCRIPTION
**	Put message error and exit.
**	PARAMETERS
**	#1. The output title (title);
**	#2. The output message (msg);
**	#3. The file descriptor (fd);
**	RETURN VALUES
**	-
*/
void	error_msg_exit(char *title, char *msg, int fd)
{
	put_msg(title, msg, fd);
	exit(EXIT_FAILURE);
}
