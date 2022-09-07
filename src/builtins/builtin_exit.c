/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 05:57:11 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/09/07 18:43:00 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '+' && *str != '-')
			return (false);
		str++;
	}
	return (true);
}

/*	GET_STATUS
**	------------
**	DESCRIPTION
**	Get the status. If the status is outside the range 0 to 255, 128 is returned
**	PARAMETERS
**	#1. The string (str);
**	RETURN VALUES
**	Return status.
*/
static int	get_status(char *str)
{
	int	status;

	status = ft_atoi(str);
	if (status < 0 || status > 255)
		status = 128;
	return (status);
}

/*	BUILTIN_EXIT
**	------------
**	DESCRIPTION
**	Builtin exit.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (head_table);
**	RETURN VALUES
**	-
*/
void	builtin_exit(t_cmdtable *head_table)
{
	int	i;
	int	status;

	i = 1;
	status = -1;
	ft_putendl_fd("exit", 2);
	while (head_table->word[i])
	{
		if (status != -1)
		{
			g_data.status = 1;
			put_msg_cmd("minishell", "exit", TOO_MANY_ARG, 2);
			return ;
		}
		if (str_is_numeric(head_table->word[i]))
			status = get_status(head_table->word[i]);
		i++;
	}
	if (status != -1)
		g_data.status = status;
	free_minishell();
	free_env_lst(&g_data.head_env);
	exit(g_data.status);
}
