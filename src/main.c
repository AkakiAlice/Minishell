/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:33:28 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/17 17:33:54 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_exit_code(char *word, t_data *data)
{
	if (ft_strncmp_eq(word, "$?", 2))
	{
		free(word);
		word = ft_strdup(ft_itoa(data->status));
	}
}

void	expand_env(char *word, t_data *data)
{
	char	**temp;

	temp = ft_split2(word, '$');
	ft_printf(temp[0]);
	(void)data;
}

void	expand(t_data *data)
{
	t_cmdtable	*temp;
	int			i;

	temp = data->head_cmd;
	while (temp)
	{
		i = 0;
		while (temp->word[i])
		{
			if (ft_strncmp_eq(temp->word[i], "$", 1))
			{
				put_exit_code(temp->word[i], data);
				expand_env(temp->word[i], data);
			}
			i++;
		}
		temp = temp->next;
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
void	run_cmd(t_data *data)
{
	tokenizer(data);
	builtin(data);
	lexer(&data->last_token, data->splited_cmdl);
	if (parser(data) == FAILURE)
		return ;
	create_cmd_table(data);
	expand(data);
	fork_it(data, &data->last_env);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	(void)argv;
	if (argc > 1)
		error_msg_exit("minishell", TOO_MANY_ARG, 2);
	minishell_init(&data);
	save_env(&data.last_env, envp);
	data.path_value = get_path(data.last_env);
	while (1)
	{
		get_prompt(&data, &data.last_env);
		if (validate_quote_closed(data.cmd_line))
			run_cmd(&data);
		else
			put_msg("minishell", UNCLOSED_QUOTES, 2);
		free_minishell(&data);
	}
	return (0);
}
