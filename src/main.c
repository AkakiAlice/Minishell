/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:33:28 by alida-si          #+#    #+#             */
/*   Updated: 2022/06/23 21:41:52 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_prompt(void)
{
	char	*cmd_line;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_strlcat(cwd, "$ ", (ft_strlen(cwd) + 3));
	while (1)
	{
		cmd_line = readline(cwd);
		if (*cmd_line)
		{
			add_history(cmd_line);
			free(cmd_line);
		}
		else
			break ;
	}
}

int	main(void)
{
	get_prompt();
	return (0);
}
