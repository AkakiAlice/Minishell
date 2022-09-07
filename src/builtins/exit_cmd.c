/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 05:57:11 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/25 07:11:14 by pmitsuko         ###   ########.fr       */
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

/*	EXIT_CMD
**	------------
**	DESCRIPTION
**	Builtin exit.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (head_table);
**	RETURN VALUES
**	-
*/
void	exit_cmd(t_data *data, t_cmdtable *head_table)
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
			data->status = 1;
			put_msg_cmd("minishell", "exit", TOO_MANY_ARG, 2);
			return ;
		}
		if (str_is_numeric(head_table->word[i]))
			status = get_status(head_table->word[i]);
		i++;
	}
	if (status != -1)
		data->status = status;
	free_minishell(data);
	free_env_lst(&data->head_env);
	exit(data->status);
}
