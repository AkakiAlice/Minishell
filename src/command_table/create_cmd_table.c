/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:05:42 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/17 07:03:41 by pmitsuko         ###   ########.fr       */
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
		// matrix_printf(cmd->word);
		// matrix_printf(cmd->less);
		// matrix_printf(cmd->great);
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
		ft_matrix_free((*head_cmd)->less);
		ft_matrix_free((*head_cmd)->great);
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
void	cmd_lst_add_front(t_cmdtable **head_cmd, char **word, char **less, char **great)
{
	t_cmdtable	*ptr;
	t_cmdtable	*temp;

	ptr = (t_cmdtable *)malloc(sizeof(t_cmdtable));
	if (!ptr)
		return ;
	ptr->word = word;
	ptr->less = less;
	ptr->great = great;
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

bool	is_less(char *cmd)
{
	int	token;

	token = get_token(cmd);
	if (token == INPUT || token == HEREDOC)
		return (true);
	return (false);
}

bool	is_great(char *cmd)
{
	int	token;

	token = get_token(cmd);
	if (token == TRUNC || token == APPEND)
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
void	save_word(t_cmdtable **head_cmd, char ***cmd, int word_counter, int less_counter, int great_counter)
{
	char	**words;
	char	**less;
	char	**great;
	int		i;
	int		j;
	int		k;

	if (word_counter)
	{
		words = (char **)malloc(((sizeof(char *)) * (word_counter + 1)));
		if (!words)
			return ;
	}
	else
		words = NULL;
	if (less_counter) // * Feito essa tratativa porque nem sempre será passado o word e less
	{
		less = (char **)malloc(((sizeof(char *)) * (less_counter + 1)));
		if (!less)
			return ;
	}
	else
		less = NULL;
	if (great_counter)
	{
		great = (char **)malloc(((sizeof(char *)) * (great_counter + 1)));
		if (!great)
			return ;
	}
	else
		great = NULL;
	i = 0;
	j = 0;
	k = 0;
	while (**cmd && (word_counter > 0 || less_counter > 0 || great_counter > 0))
	{
		if (less_counter > 0 && is_less(**cmd))
		{
			less[j++] = ft_strdup(**cmd); // Redirect
			(*cmd)++;
			less[j++] = ft_strdup(**cmd); // File
			(*cmd)++;
			less_counter -= 2;
		}
		else if (great_counter > 0 && is_great(**cmd))
		{
			great[k++] = ft_strdup(**cmd); // Redirect
			(*cmd)++;
			great[k++] = ft_strdup(**cmd); // File
			(*cmd)++;
			great_counter -= 2;
		}
		else if (word_counter > 0)
		{
			words[i++] = str_without_quotes(**cmd);
			(*cmd)++;
			word_counter--;
		}
	}
	if (i > 0)
		words[i] = NULL;
	if (j > 0)
		less[j] = NULL;
	if (k > 0)
		great[k] = NULL;
	cmd_lst_add_front(head_cmd, words, less, great);
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
	int		less_counter;
	int		great_counter;
	bool	is_redirect;

	word_counter = 0;
	less_counter = 0;
	great_counter = 0;
	is_redirect = false;
	while (head_token != NULL)
	{
		if (head_token->value == PIPE)
		{
			save_word(head_cmd, &cmd, word_counter, less_counter, great_counter);
			word_counter = 0;
			less_counter = 0;
			great_counter = 0;
			cmd++;
		}
		else if (head_token->value == INPUT || head_token->value == HEREDOC)
		{
			is_redirect = true;
			less_counter += 2;
		}
		else if (head_token->value == TRUNC || head_token->value == APPEND)
		{
			is_redirect = true;
			great_counter += 2;
		}
		else if (head_token->value == WORD)
		{
			if (is_redirect)
				is_redirect = false;
			else
				word_counter++;
		}
		head_token = head_token->next;
	}
	if (word_counter || less_counter || great_counter)
		save_word(head_cmd, &cmd, word_counter, less_counter, great_counter);
}
