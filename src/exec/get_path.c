/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:51:39 by alida-si          #+#    #+#             */
/*   Updated: 2022/07/12 15:21:24 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_env *env_list)
{
	t_env *ptr;

	ptr = env_list;
	while (ptr->next != env_list)
	{
		if (ft_strncmp("PATH", ptr->name, 4) == 0)
			return (ptr->value);
		ptr = ptr->next;
	}
	return (ptr->value);
}