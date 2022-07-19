/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:06:33 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/19 14:16:47 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	PUT_MSG
**	------------
**	DESCRIPTION
**	Put message in 'title: description' format.
**	PARAMETERS
**	#1. The string (title);
**	#1. The string (msg);
**	#1. The number (fd);
**	RETURN VALUES
**	-
*/
void	put_msg(char *title, char *msg, int fd)
{
	ft_putstr_fd(title, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(msg, fd);
}
