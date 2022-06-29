/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:50:31 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/06/29 08:03:44 by pmitsuko         ###   ########.fr       */
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

int	check_cmd_char(t_token **last_token, char *cmd)
{
	if (ft_strncmp_eq(cmd, "|", 1))
		return (token_lst_add_back(last_token, PIPE));
	if (ft_strncmp_eq(cmd, "<<", 2))
		return (token_lst_add_back(last_token, HEREDOC));
	if (ft_strncmp_eq(cmd, "<", 1))
		return (token_lst_add_back(last_token, INPUT));
	if (ft_strncmp_eq(cmd, ">>", 2))
		return (token_lst_add_back(last_token, APPEND));
	if (ft_strncmp_eq(cmd, ">", 1))
		return (token_lst_add_back(last_token, TRUNC));
	return (token_lst_add_back(last_token, WORD));
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
			token_lst_add_back(last_token, WORD);
		i++;
	}
	return ;
}
