/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:42:40 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/09 08:37:51 by pmitsuko         ###   ########.fr       */
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
void	tokenizer(t_data *data)
{
	data->splited_cmdl = split_cmd(data->cmd_line);
}
