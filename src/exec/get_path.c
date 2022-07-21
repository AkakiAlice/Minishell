/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:51:39 by alida-si          #+#    #+#             */
/*   Updated: 2022/07/21 19:11:13 by alida-si         ###   ########.fr       */
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
char	*get_path(t_env *env_list)
{
	t_env	*ptr;

	ptr = env_list;
	while (ptr->next != env_list)
	{
		if (ft_strncmp("PATH", ptr->name, 4) == 0)
			return (ptr->value);
		ptr = ptr->next;
	}
	return (ptr->value);
}
