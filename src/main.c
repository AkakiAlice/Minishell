/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:33:28 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/07 15:05:21 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	RUN_CMD
**	------------
**	DESCRIPTION
**	Calls the parsing functions and executes the command.
**	PARAMETERS
**	#1. The pointer to struct data (data);
**	#2. The pointer to path value (path_value);
**	RETURN VALUES
**	-
*/
void	run_cmd(t_data *data)
{
	tokenizer(data);
	if (data->splited_cmdl == NULL)
		return ;
	lexer(&data->head_token, data->splited_cmdl);
	if (parser(data) == FAILURE)
		return ;
	create_cmd_table(&data->head_cmd, data->head_token, data->splited_cmdl);
	expand(data);
	open_pipe(data);
	open_redirection(data);
	if (!g_data.interrupt_heredoc)
		fork_it(data, &data->head_env);
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	if (argc > 1)
		error_msg_exit("minishell", TOO_MANY_ARG, 2);
	minishell_init();
	save_env(envp);
	g_data.path_value = search_env_value("PATH");
	while (1)
	{
		signal(SIGINT, sig_handle_minishell);
		signal(SIGQUIT, SIG_IGN);
		get_prompt(&g_data, &g_data.head_env);
		if (*g_data.cmd_line)
		{
			if (validate_quote_closed(g_data.cmd_line))
				run_cmd(&g_data);
			else
				put_msg("minishell", UNCLOSED_QUOTES, 2);
			free_minishell(&g_data);
		}
	}
	return (0);
}
