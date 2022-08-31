/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 06:11:32 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/25 07:06:29 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	EXEC_BUILTIN_PARENT
**	------------
**	DESCRIPTION
**	Execute the builtins in the parent process.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	#2. The pointer to list (head_table);
**	RETURN VALUES
**	-
*/
int	exec_builtin_parent(t_data *data, t_cmdtable *head_table)
{
	if (strcmp_eq(*head_table->word, "exit"))
	{
		if (!data->is_pipe)
			exit_cmd(data, head_table);
		return (1);
	}
	return (0);
}
