/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:50:31 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/14 19:05:43 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	GET_TOKEN
**	------------
**	DESCRIPTION
**	Check the cmd character is pipe, heredoc, input, append, trunc or word.
**	PARAMETERS
**	#1. The array (cmd);
**	RETURN VALUES
**	Return token
*/
int	get_token(char *cmd)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd);
	if (cmd_len > 2)
		return (WORD);
	if (cmd_len == 1 && ft_strncmp_eq(cmd, "|", 1))
		return (PIPE);
	if (cmd_len == 2 && ft_strncmp_eq(cmd, "<<", 2))
		return (HEREDOC);
	if (cmd_len == 1 && ft_strncmp_eq(cmd, "<", 1))
		return (INPUT);
	if (cmd_len == 2 && ft_strncmp_eq(cmd, ">>", 2))
		return (APPEND);
	if (cmd_len == 1 && ft_strncmp_eq(cmd, ">", 1))
		return (TRUNC);
	return (WORD);
}

/*	LEXER
**	------------
**	DESCRIPTION
**	Loops through the cmd matrix and does lexer.
**	PARAMETERS
**	#1. The pointer to list (head_token);
**	#2. The array of pointers (cmd);
**	RETURN VALUES
**	-
*/
void	lexer(t_token **head_token, char **cmd)
{
	int	i;
	int	token;

	i = 0;
	while (cmd[i])
	{
		token = get_token(cmd[i]);
		token_lst_add_back(head_token, token);
		i++;
	}
	return ;
}
