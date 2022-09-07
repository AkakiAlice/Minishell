/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:42:40 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/07 16:16:43 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	TOKENIZER
**	------------
**	DESCRIPTION
**	Create tokens from the command line using space as a separator.
**	PARAMETERS
**	#1. The pointer to structure that contains the command line (data);
**	RETURN VALUES
**	-
*/
void	tokenizer(void)
{
	g_data.splited_cmdl = split_cmd(g_data.cmd_line);
}
