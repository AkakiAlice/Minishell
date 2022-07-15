/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:33:28 by alida-si          #+#    #+#             */
/*   Updated: 2022/07/14 19:14:23 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	t_env	*last_env;
	char	*oi;

	last_env = NULL;
	save_env(&last_env, envp);
	oi = get_path(last_env);
	while (1)
	{
		get_prompt(&data);
		tokenizer(&data);
		check_cmd(oi, &data);
		fork_it(&data);
		free(data.cmd_line);
		ft_matrix_free(data.splited_cmdl);
	}
	ft_printf("%i\n%s\n", argc, argv[0]);
	return (0);
}
