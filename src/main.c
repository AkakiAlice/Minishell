/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:33:28 by alida-si          #+#    #+#             */
/*   Updated: 2022/07/22 06:06:34 by pmitsuko         ###   ########.fr       */
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
		error_msg_exit("minishell", TOO_MANY_ARG, 2);
	while (1)
	{
		get_prompt(&data);
		if (!validate_quote_closed(data.cmd_line))
		{
			put_msg("minishell", UNCLOSED_QUOTES, 2, 1);
			free(data.cmd_line);
		}
		else
		{
			tokenizer(&data);
			if (ft_strncmp_eq(data.splited_cmdl[0], "exit", 4))
				exit_cmd(&data);
			last_token = NULL;
			lexer(&last_token, data.splited_cmdl);
			parser(last_token);
			free_token_lst(&last_token);
			free(data.cmd_line);
			ft_matrix_free(data.splited_cmdl);
		}
	}
	return (0);
}
