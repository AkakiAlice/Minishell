/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:59:00 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/27 15:52:20 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	MINISHELL_INIT
**	------------
**	DESCRIPTION
**	Initialize values from data struct.
**	PARAMETERS
**	#1. Pointer to struct data (data);
**	RETURN VALUES
**	-
*/
void	minishell_init(t_data *data)
{
	data->head_cmd = NULL;
	data->head_env = NULL;
	data->cmd_path = NULL;
	data->cmd_line = NULL;
	data->head_token = NULL;
	data->splited_cmdl = NULL;
	data->status = 0;
	data->is_pipe = false;
	data->signal = 0;
}
