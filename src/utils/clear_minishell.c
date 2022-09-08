/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 07:17:18 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/08 07:42:20 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	CLEAR_MINISHELL
**	------------
**	DESCRIPTION
**	Free allocation memory in data struct and initialize values.
**	PARAMETERS
**	-
**	RETURN VALUES
**	-
*/
void	clear_minishell(void)
{
	if (g_data.cmd_line != NULL)
	{
		free(g_data.cmd_line);
		g_data.cmd_line = NULL;
	}
	ft_matrix_free(&g_data.splited_cmdl);
	g_data.splited_cmdl = NULL;
	free_env_lst(&g_data.head_env);
	free_token_lst(&g_data.head_token);
	free_cmd_lst(&g_data.head_cmd);
	g_data.is_pipe = false;
	g_data.interrupt_heredoc = false;
}
