/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 06:57:58 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/27 07:14:54 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ERROR_MSG_EXIT
**	------------
**	DESCRIPTION
**	Put message error and exit.
**	PARAMETERS
**	#1. The string (title);
**	#1. The string (msg);
**	#1. The number (fd);
**	RETURN VALUES
**	-
*/
void	error_msg_exit(char *title, char *msg, int fd)
{
	put_msg(title, msg, fd);
	exit(EXIT_FAILURE);
}
