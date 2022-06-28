/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:42:40 by alida-si          #+#    #+#             */
/*   Updated: 2022/06/27 18:28:40 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(t_data *data)
{
	int	i = 0;
	data->splited_cmdl = ft_split2(data->cmd_line, ' ');
	while (data->splited_cmdl[i] != NULL)
	{
		ft_printf("%s\n", data->splited_cmdl[i]);
		i++;
	}
}
