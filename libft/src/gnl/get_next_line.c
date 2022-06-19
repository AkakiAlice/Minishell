/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:44:38 by alida-si          #+#    #+#             */
/*   Updated: 2021/09/18 11:00:55 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!save)
	{
		save = ft_strdup("");
		if (!save)
			return (NULL);
	}
	line = get_line(fd, &buffer, &save);
	if (!line)
		free(line);
	free(buffer);
	return (line);
}

char	*get_line(int fd, char **buffer, char **save)
{
	int		count;
	char	*aux_swap;

	if (ft_strchr(*save, '\n'))
		return (extract_line(save));
	count = do_read(fd, buffer, save);
	if ((count == 0 || count == -1) && !**save)
	{
		free(*save);
		*save = NULL;
		return (NULL);
	}
	if (ft_strchr(*save, '\n'))
		return (extract_line(save));
	if (!ft_strchr(*save, '\n') && **save)
	{
		aux_swap = ft_strdup(*save);
		free(*save);
		*save = NULL;
		return (aux_swap);
	}
	return (NULL);
}

int	do_read(int fd, char **buffer, char **save)
{
	int		count;
	char	*aux_swap;

	count = 1;
	while (!ft_strchr(*save, '\n') && count)
	{
		count = read(fd, *buffer, BUFFER_SIZE);
		if (count == -1)
			return (count);
		(*buffer)[count] = '\0';
		aux_swap = *save;
		*save = ft_strjoin(aux_swap, *buffer);
		free(aux_swap);
	}
	return (count);
}

char	*extract_line(char **save)
{
	char	*line;
	char	*aux;
	int		i;

	i = 0;
	while ((*save)[i] != '\n' && (*save)[i] != '\0')
		i++;
	aux = *save;
	line = ft_substr(aux, 0, i + 1);
	*save = ft_strdup(&(*save)[i + 1]);
	free(aux);
	return (line);
}
