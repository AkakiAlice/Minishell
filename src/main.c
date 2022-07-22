/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:33:28 by alida-si          #+#    #+#             */
/*   Updated: 2022/07/22 18:03:06 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	t_token	*last_token;
	t_env	*last_env;
	char	*oi;

	(void)argv;
	if (argc > 1)
		error_msg_exit("minishell", TOO_MANY_ARG, 2);
	last_env = NULL;
	data.cmd_path = NULL;
	data.cmd_line = NULL;
	save_env(&last_env, envp);
	oi = get_path(last_env);
	while (1)
	{
		get_prompt(&data, &last_env);
		if (!validate_quote_closed(data.cmd_line))
		{
			put_msg("minishell", UNCLOSED_QUOTES, 2, 1);
			free(data.cmd_line);
		}
		else
		{
			tokenizer(&data);
			builtin(&data);
			last_token = NULL;
			lexer(&last_token, data.splited_cmdl);
			parser(last_token);
			check_cmd(oi, &data);
			fork_it(&data, &last_env);
			free_token_lst(&last_token);
			free(data.cmd_line);
			ft_matrix_free(data.splited_cmdl);
		}
	}
	return (0);
}
