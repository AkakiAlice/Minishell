/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:33:28 by alida-si          #+#    #+#             */
/*   Updated: 2022/07/18 07:01:42 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	t_token	*last_token;

	(void)argv;
	(void)envp;
	if (argc > 1)
		error_msg_exit(TOO_MANY_ARG, 2);
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
