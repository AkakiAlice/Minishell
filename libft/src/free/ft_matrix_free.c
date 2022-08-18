/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 07:50:44 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/18 05:57:00 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	FT_MATRIX_FREE
**	------------
**	DESCRIPTION
**	Free all memory allocated within matrix.
**	PARAMETERS
**	#1. The pointer to array of strings (matrix);
**	RETURN VALUES
**	-
*/
void	ft_matrix_free(char ***matrix)
{
	int	i;

	i = 0;
	if (!(*matrix))
		return ;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
	*matrix = NULL;
	return ;
}
