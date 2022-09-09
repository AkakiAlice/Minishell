/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 05:57:11 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/09 06:10:58 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "limits.h"

/*	STR_IS_NUMERIC
**	------------
**	DESCRIPTION
**	Checks if the string is a numeric value.
**	PARAMETERS
**	#1. The string (str);
**	RETURN VALUES
**	Return true if it is and false if not
*/
static bool	str_is_numeric(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (!ft_isdigit(*str))
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

/*	BUILTIN_EXIT
**	------------
**	DESCRIPTION
**	Builtin exit.
**	PARAMETERS
**	#1. The pointer to list (head_table);
**	RETURN VALUES
**	-
*/
void	builtin_exit(t_cmdtable *head_table)
{
	int	status;

	status = 1;
	ft_putendl_fd("exit", 1);
	if (head_table->word[1] != NULL)
	{
		if (head_table->word[2] != NULL)
		{
			g_data.status = 1;
			put_msg_cmd("minishell", "exit", TOO_MANY_ARG, 2);
			return ;
		}
		if (str_is_numeric(head_table->word[1]))
			status = ft_atoi(head_table->word[1]);
		else
		{
			g_data.status = 2;
			put_msg_cmd("minishell", "exit", NUM_REQ, 2);
			return ;
		}
	}
	g_data.status = status;
	clear_minishell();
	exit(g_data.status);
}
