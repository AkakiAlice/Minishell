/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:33:28 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/18 18:44:01 by alida-si         ###   ########.fr       */
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

char	*get_var_value_expand(t_env *env_list, char *var)
{
	t_env	*ptr;

	ptr = env_list;
	while (ptr->next != env_list)
	{
		if (ft_strncmp(var, ptr->name, 4) == 0)
			return (ptr->value);
		ptr = ptr->next;
	}
	if (ft_strncmp(var, ptr->name, 4) == 0)
			return (ptr->value);
	return (ft_strdup(""));
}

char	*expand_env(char *word, t_data *data)
{
	char	**temp;
	char	*value;

	if (!ft_strncmp_eq(word, "$?", 2))
	{
		temp = ft_split2(word, '$');
		value = get_var_value_expand(data->head_env, temp[0]);
		ft_matrix_free(&temp);
	}
	return (value);
}

void	expand(t_data *data)
{
	t_cmdtable	*temp;
	int			i;
	char		*aux;

	temp = data->head_cmd;
	while (temp)
	{
		i = 0;
		while (temp->word[i])
		{
			if (ft_strncmp_eq(temp->word[i], "$", 1))
			{
				if (!ft_strncmp_eq(temp->word[i], "$?", 2))
				{
					aux = expand_env(temp->word[i], data);
					free(temp->word[i]);
					temp->word[i] = ft_strdup(aux);
				}
				put_exit_code(temp->word[i], data);
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
	lexer(&data->head_token, data->splited_cmdl);
	if (parser(data) == FAILURE)
		return ;
	create_cmd_table(&data->head_cmd, data->head_token, data->splited_cmdl);
	expand(data);
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
