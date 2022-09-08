/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:07:42 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/08 14:10:00 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	SYNTAX_ERROR
**	------------
**	DESCRIPTION
**	Output message and set exit code.
**	PARAMETERS
**	#1. The output message (msg);
**	RETURN VALUES
**	Return 1
*/
int	syntax_error(char *msg)
{
	put_msg("minishell", msg, 2);
	g_data.status = 2;
	return (1);
}
