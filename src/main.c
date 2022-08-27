/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:33:28 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/27 14:23:51 by alida-si         ###   ########.fr       */
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
	// builtin(data);
	lexer(&data->head_token, data->splited_cmdl);
	if (parser(data) == FAILURE)
		return ;
	create_cmd_table(&data->head_cmd, data->head_token, data->splited_cmdl);
	expand(data);
	open_pipe(data);
	open_redirection(data);
	fork_it(data, &data->head_env);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	(void)argv;
	if (argc > 1)
		error_msg_exit("minishell", TOO_MANY_ARG, 2);
	minishell_init(&data);
	save_env(&data.head_env, envp);
	data.path_value = get_path(data.head_env);
	while (1)
	{
		get_prompt(&data, &data.head_env);
		if (validate_quote_closed(data.cmd_line))
			run_cmd(&data);
		else
			put_msg("minishell", UNCLOSED_QUOTES, 2);
		free_minishell(&data);
	}
	return (0);
}
