/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 05:57:11 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/22 05:59:06 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_cmd(t_data *data)
{
	free(data->cmd_line);
	ft_matrix_free(data->splited_cmdl);
	exit(EXIT_SUCCESS);
}
