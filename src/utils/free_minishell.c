/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:59:54 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/31 07:33:25 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	FREE_MINISHELL
**	------------
**	DESCRIPTION
**	Free allocation memory in data struct.
**	PARAMETERS
**	#1. Pointer to struct data (data);
**	RETURN VALUES
**	-
*/
void	free_minishell(t_data *data)
{
	free_token_lst(&data->head_token);
	if (data->cmd_line != NULL)
	{
		free(data->cmd_line);
		data->cmd_line = NULL;
	}
	free_cmd_lst(&data->head_cmd);
	ft_matrix_free(&data->splited_cmdl);
	data->splited_cmdl = NULL;
	data->is_pipe = false;
	data->interrupt_heredoc = false;
}
