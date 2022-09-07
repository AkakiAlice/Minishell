/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:59:54 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/07 19:04:03 by alida-si         ###   ########.fr       */
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
void	free_minishell(void)
{
	free_token_lst(&g_data.head_token);
	if (g_data.cmd_line != NULL)
	{
		free(g_data.cmd_line);
		g_data.cmd_line = NULL;
	}
	free_cmd_lst(&g_data.head_cmd);
	ft_matrix_free(&g_data.splited_cmdl);
	g_data.splited_cmdl = NULL;
	g_data.is_pipe = false;
	g_data.interrupt_heredoc = false;
}
