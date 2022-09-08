/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:05:42 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/08 13:56:58 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	SAFE_CMD_V
**	------------
**	DESCRIPTION
**	Save NULL in last array in cmd table values.
**	PARAMETERS
**	#1. Pointer to cmd value struct (cmd_value);
**	#2. Pointer to counter struct (index);
**	RETURN VALUES
**	-
*/
static void	safe_cmd_v(t_cmd_value *cmd_value, t_counter index)
{
	if (index.word > 0)
		cmd_value->word[index.word] = NULL;
	if (index.redirect > 0)
		cmd_value->redirect[index.redirect] = NULL;
}

/*	SAVE_TABLE_VALUE
**	------------
**	DESCRIPTION
**	Save the table value without quotes
**	PARAMETERS
**	#1. Pointer to string array (table_v);
**	#2. Pointer to string array (cmd);
**	#3. Pointer to integer (i);
**	#4. Pointer to integer (count);
**	RETURN VALUES
**	-
*/
static void	save_table_value(char ***table_v, char ***cmd, int *i, int *count)
{
	if (is_var_expansion(**cmd))
		(*table_v)[(*i)++] = ft_strdup(**cmd);
	else
		(*table_v)[(*i)++] = str_without_quotes(**cmd);
	(*cmd)++;
	(*count)--;
}

/*	SAVE_CMD_LINE
**	------------
**	DESCRIPTION
**	Save the number of table values equal to the counter.
**	PARAMETERS
**	#1. Pointer to struct command table (head_cmd);
**	#2. Pointer to string array (cmd);
**	#2. Pointer to struct count (count);
**	RETURN VALUES
**	-
*/
static void	save_cmd_line(t_cmdtable **head_cmd, char ***cmd, t_counter *count)
{
	t_cmd_value	cmd_v;
	t_counter	index;

	init_cmd_value(&cmd_v, count);
	init_count(&index);
	while (**cmd && (count->word > 0 || count->redirect > 0))
	{
		if (count->redirect > 0 && is_redirect(**cmd))
		{
			save_table_value(&cmd_v.redirect, cmd, &index.redirect,
				&count->redirect);
			save_table_value(&cmd_v.redirect, cmd, &index.redirect,
				&count->redirect);
		}
		else if (count->word > 0)
			save_table_value(&cmd_v.word, cmd, &index.word, &count->word);
	}
	safe_cmd_v(&cmd_v, index);
	cmd_lst_add_front(head_cmd, cmd_v);
}

/*	COUNT_WORD_AND_REDIRECT
**	------------
**	DESCRIPTION
**	Check token to do count word and redirection.
**	PARAMETERS
**	#1. Integer (token)
**	#2. Pointer to struct count (count);
**	RETURN VALUES
**	Return true if token is redirect and false if word.
*/
static bool	count_word_and_redirect(int token, t_counter *count)
{
	if (token == INPUT || token == HEREDOC || token == TRUNC || token == APPEND)
	{
		count->redirect += 2;
		return (true);
	}
	else if (token == WORD)
		count->word++;
	return (false);
}

/*	CREATE_CMD_TABLE
**	------------
**	DESCRIPTION
**	Create the command table. Whenever there is a pipe, a new node is inserted
**	in the linked list.
**	PARAMETERS
**	-
**	RETURN VALUES
**	-
*/
void	create_cmd_table(void)
{
	t_counter	count;
	t_token		*head_token;
	char		**cmd;

	head_token = g_data.head_token;
	init_count(&count);
	cmd = g_data.splited_cmdl;
	while (head_token != NULL)
	{
		if (head_token->value == PIPE)
		{
			save_cmd_line(&g_data.head_cmd, &cmd, &count);
			init_count(&count);
			cmd++;
		}
		else if (count_word_and_redirect(head_token->value, &count))
			head_token = head_token->next;
		head_token = head_token->next;
	}
	if (count.word || count.redirect)
		save_cmd_line(&g_data.head_cmd, &cmd, &count);
}
