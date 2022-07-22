/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 06:11:32 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/22 06:14:19 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin(t_data *data)
{
	if (ft_strlen(data->splited_cmdl[0]) == 4
		&& ft_strncmp_eq(data->splited_cmdl[0], "exit", 4))
		exit_cmd(data);
}
