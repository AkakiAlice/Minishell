/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:51:39 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/07 15:49:13 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	GET_PATH
**	------------
**	DESCRIPTION
**	Loops through the environment list and look for the PATH value.
**	PARAMETERS
**	#1. The pointer to list (env_list);
**	RETURN VALUES
**	Returns the string of the PATH value
*/
char	*search_env_value(char *var)
{
	t_env	*ptr;

	ptr = g_data.head_env;
	while (ptr != NULL)
	{
		if (strcmp_eq(var, ptr->name))
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}
