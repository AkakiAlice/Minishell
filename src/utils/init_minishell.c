/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:59:00 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/28 14:15:58 by pmitsuko         ###   ########.fr       */
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
	data->interrupt_heredoc = false;
}
