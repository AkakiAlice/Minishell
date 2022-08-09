/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_with_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 06:18:43 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/09 06:18:57 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	SKIP_QUOTES
**	------------
**	DESCRIPTION
**	Checks the type of quotes and skips to the closing quotes.
**	PARAMETERS
**	#1. The pointer of command line (cmd);
**	RETURN VALUES
**	-
*/
void	skip_quotes(char **cmd)
{
	int	quote_type;

	quote_type = is_quote_type(**cmd);
	if (quote_type != -1)
	{
		(*cmd)++;
		while (**cmd && **cmd != quote_type)
			(*cmd)++;
	}
	return ;
}
