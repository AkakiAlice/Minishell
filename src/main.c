/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:33:28 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/18 07:42:02 by pmitsuko         ###   ########.fr       */
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
	lexer(&data->head_token, data->splited_cmdl);
	if (parser(data) == FAILURE)
		return ;
	create_cmd_table(&data->head_cmd, data->head_token, data->splited_cmdl);
	check_cmd(path_value, data);
	open_redirection(data);
	fork_it(data, &data->head_env);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	char	*path_value;

	(void)argv;
	if (argc > 1)
		error_msg_exit("minishell", TOO_MANY_ARG, 2);
	minishell_init(&data);
	save_env(&data.head_env, envp);
	path_value = get_path(data.head_env);
	while (1)
	{
		get_prompt(&data, &data.head_env);
		if (validate_quote_closed(data.cmd_line))
			run_cmd(&data, path_value);
		else
			put_msg("minishell", UNCLOSED_QUOTES, 2);
		free_minishell(&data);
	}
	return (0);
}
