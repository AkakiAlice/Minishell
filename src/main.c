/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:33:28 by alida-si          #+#    #+#             */
/*   Updated: 2022/07/07 07:47:13 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	data;
	t_token	*last_token;

	while (1)
	{
		get_prompt(&data);
		tokenizer(&data);
		last_token = NULL;
		lexer(&last_token, data.splited_cmdl);
		free_token_lst(&last_token);
		free(data.cmd_line);
		ft_matrix_free(data.splited_cmdl);
	}
	return (0);
}
