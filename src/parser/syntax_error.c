/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:07:42 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/20 17:50:44 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	SYNTAX_ERROR
**	------------
**	DESCRIPTION
**	Output message and set exit code.
**	PARAMETERS
**	#1. The pointer to data struct (data);
**	#2. The output message (msg);
**	RETURN VALUES
**	Return 1
*/
int	syntax_error(t_data *data, char *msg)
{
	put_msg("minishell", msg, 2);
	data->status = 2;
	return (1);
}
