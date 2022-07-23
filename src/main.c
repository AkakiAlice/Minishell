/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:33:28 by alida-si          #+#    #+#             */
/*   Updated: 2022/07/23 15:38:41 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_exit_code(t_data *data)
{
	if (ft_strchr(data->cmd_line, '$') != NULL)
	{
		free(data->splited_cmdl[1]);
		data->splited_cmdl[1] = ft_strdup(ft_itoa(data->status));
	}
}

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
void	run_cmd(t_data *data, char	*path_value)
{
	tokenizer(data);
	put_exit_code(data);
	builtin(data);
	lexer(&data->last_token, data->splited_cmdl);
	parser(data->last_token);
	check_cmd(path_value, data);
	fork_it(data, &data->last_env);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	char	*path_value;

	(void)argv;
	(void)argc;
	/*if (argc > 1)
		error_msg_exit("minishell", TOO_MANY_ARG, 2);*/
	minishell_init(&data);
	save_env(&data.last_env, envp);
	path_value = get_path(data.last_env);
	while (1)
	{
		get_prompt(&data, &data.last_env);
		if (validate_quote_closed(data.cmd_line))
			run_cmd(&data, path_value);
		else
			put_msg("minishell", UNCLOSED_QUOTES, 2, 1);
		free_minishell(&data);
	}
	return (0);
}
