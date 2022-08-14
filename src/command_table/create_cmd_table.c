/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:05:42 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/14 19:14:31 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ! Função temporária
void	matrix_printf(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (*(matrix + i))
	{
		ft_printf("[%s]\n", *(matrix + i));
		i++;
	}
	return ;
}

// ! Função temporária
void	cmdlst_printf(t_cmdtable *cmd)
{
	int	i;

	i = 0;
	while (cmd != NULL)
	{
		ft_printf("List: [%d]\n", i++);
		matrix_printf(cmd->word);
		cmd = cmd->next;
	}
	return ;
}

/*	FREE_TOKEN_LST
**	------------
**	DESCRIPTION
**	Free all memory allocated within command singly linked list.
**	PARAMETERS
**	#1. The pointer to the first element of the list (head_cmd);
**	RETURN VALUES
**	-
*/
void	free_cmd_lst(t_cmdtable **head_cmd)
{
	t_cmdtable	*temp;

	if (*head_cmd == NULL)
		return ;
	while (*head_cmd != NULL)
	{
		ft_matrix_free((*head_cmd)->word);
		temp = (*head_cmd)->next;
		free(*head_cmd);
		*head_cmd = temp;
	}
}

/*	CMD_LST_ADD_FRONT
**	------------
**	DESCRIPTION
**	Add the new node at the end of the singly linked list.
**	PARAMETERS
**	#1. The pointer to list (head_cmd);
**	#2. The word array (word);
**	RETURN VALUES
**	-
*/
void	cmd_lst_add_front(t_cmdtable **head_cmd, char **word)
{
	t_cmdtable	*ptr;
	t_cmdtable	*temp;

	ptr = (t_cmdtable *)malloc(sizeof(t_cmdtable));
	if (!ptr)
		return ;
	ptr->word = word;
	if ((*head_cmd) == NULL)
	{
		ptr->next = NULL;
		*head_cmd = ptr;
	}
	else
	{
		temp = *head_cmd;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = ptr;
		ptr->next = NULL;
	}
}

bool	is_redirect(char *cmd)
{
	int	token;

	token = get_token(cmd);
	if (token != WORD && token != PIPE)
		return (true);
	return (false);
}

/*	SAVE_WORD
**	------------
**	DESCRIPTION
**	Save the number of words equal to the counter.
**	PARAMETERS
**	#1. Word counter (word_counter);
**	#2. Pointer to string array (cmd);
**	RETURN VALUES
**	Return allocated memory from new array of string.
*/
char	**save_word(int word_counter, char ***cmd)
{
	char	**words;
	int		i;

	words = (char **)malloc(((sizeof(char *)) * (word_counter + 1)));
	if (!words)
		return (NULL);
	i = 0;
	while (**cmd && word_counter > 0)
	{
		if (is_redirect(**cmd))
			(*cmd) += 2;
		else
		{
			words[i++] = str_without_quotes(**cmd);
			(*cmd)++;
			word_counter--;
		}
	}
	words[i] = NULL;
	return (words);
}

/*	CREATE_CMD_TABLE
**	------------
**	DESCRIPTION
**	Create the command table. Whenever there is a pipe, a new node is inserted
**	in the linked list
**	PARAMETERS
**	#1. Pointer to struct command table (head_cmd);
**	#2. Pointer to struct token (head_token);
**	#3. Pointer to string (cmd);
**	RETURN VALUES
**	-
*/
void	create_cmd_table(t_cmdtable **head_cmd, t_token *head_token, char **cmd)
{
	int		word_counter;
	bool	is_file;

	word_counter = 0;
	is_file = false;
	while (head_token != NULL)
	{
		if (head_token->value == PIPE)
		{
			cmd_lst_add_front(head_cmd, save_word(word_counter, &cmd));
			word_counter = 0;
			cmd++;
		}
		else if (head_token->value == INPUT)
			is_file = true;
		else if (head_token->value == WORD)
		{
			if (is_file)
				is_file = false;
			else
				word_counter++;
		}
		head_token = head_token->next;
	}
	// ft_printf("word_counter: [%d]\n", word_counter);
	if (word_counter)
		cmd_lst_add_front(head_cmd, save_word(word_counter, &cmd));
	// cmdlst_printf(*head_cmd);
}
