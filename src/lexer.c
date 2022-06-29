/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:50:31 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/06/29 07:34:10 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	TOKEN_LST_ADD_BACK
**	------------
**	DESCRIPTION
**	Add the node at the end of the circular linked list and change the
**	last_token pointer to the last node added.
**	PARAMETERS
**	#1. The pointer to list (last_token);
**	#3. The pointer to token value (value);
**	RETURN VALUES
**	Return 0 if successful and 1 if there is memory allocation error
*/
int	token_lst_add_back(t_token **last_token, int value)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (EXIT_FAILURE);
	new_node->value = value;
	if ((*last_token) == NULL)
		new_node->next = new_node;
	else
	{
		new_node->next = (*last_token)->next;
		(*last_token)->next = new_node;
	}
	*last_token = new_node;
	return (EXIT_SUCCESS);
}

/*	FREE_TOKEN_LST
**	------------
**	DESCRIPTION
**	Free all memory allocated within token circular linked list.
**	PARAMETERS
**	#1. The pointer to last element list (last_token);
**	RETURN VALUES
**	-
*/
void	free_token_lst(t_token **last_token)
{
	t_token	*temp;
	t_token	*current;

	if (*last_token == NULL)
		return ;
	current = (*last_token)->next;
	while (current != (*last_token))
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	free((*last_token));
	*last_token = NULL;
}

/*	FT_STRNCMP_EQ
**	------------
**	DESCRIPTION
**	Compares s1 and s2 not more than n characters.
**	PARAMETERS
**	#1. The string (s1);
**	#2. The string (s2);
**	#3. The amount of character will be compared (n);
**	RETURN VALUES
**	Return 1 if strings are equal and 0 if it's different.
*/
int	ft_strncmp_eq(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (*(s1 + i) || *(s2 + i)))
	{
		if (*(s1 + i) != *(s2 + i))
			return (0);
		i++;
	}
	return (1);
}

void	check_cmd_char(t_token **last_token, char *cmd)
{
	if (ft_strncmp_eq(cmd, "|", 1))
		token_lst_add_back(last_token, PIPE);
}

void	lexer(t_token **last_token, char **cmd)
{
	int	i;
	int	cmd_len;

	i = 0;
	while (cmd[i])
	{
		cmd_len = ft_strlen(cmd[i]);
		if (cmd_len < 3)
			check_cmd_char(last_token, cmd[i]);
		else
			token_lst_add_back(last_token, -1);
		i++;
	}
	return ;
}
