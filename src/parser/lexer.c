/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:50:31 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/22 18:06:14 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	CHECK_CMD_CHAR
**	------------
**	DESCRIPTION
**	Check the cmd character is pipe, heredoc, input, append, trunc or word.
**	Then add the node at the end of circular linked list.
**	PARAMETERS
**	#1. The pointer to list (last_token);
**	#2. The array (cmd);
**	RETURN VALUES
**	Return 0 if successful and 1 if there is memory allocation error
*/
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

/*	LEXER
**	------------
**	DESCRIPTION
**	Loops through the cmd matrix and does lexer.
**	PARAMETERS
**	#1. The pointer to list (last_token);
**	#2. The array of pointers (cmd);
**	RETURN VALUES
**	-
*/
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
