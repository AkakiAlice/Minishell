/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 05:24:41 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/21 06:14:20 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_token *last_token)
{
	t_token	*current;

	if (last_token == NULL)
		return (0);
	current = last_token->next;
	if (current->value == PIPE)
	{
		put_msg("minishell", "syntax error near unexpected token `|'", 2);
		return (1);
	}
	while (current != last_token)
	{
		if (current->value == PIPE && current->next->value == PIPE)
		{
			put_msg("minishell", "syntax error near unexpected token `|'", 2);
			return (1);
		}
		current = current->next;
	}
	return (0);
}
