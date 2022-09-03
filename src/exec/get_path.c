/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:51:39 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/03 13:24:02 by alida-si         ###   ########.fr       */
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
	while (ptr != NULL)
	{
		if (ft_strncmp("PATH", ptr->name, 4) == 0)
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}
