/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 06:11:32 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/23 15:14:17 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin(t_data *data)
{
	if (ft_strlen(data->splited_cmdl[0]) == 4
		&& ft_strncmp_eq(data->splited_cmdl[0], "exit", 4))
		exit_cmd(data);
}
