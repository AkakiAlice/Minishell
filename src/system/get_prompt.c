/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:23:48 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/09 13:50:07 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	FREE_PROMPT_LINE
**	------------
**	DESCRIPTION
**	Frees the pointers that make up the command line.
**	PARAMETERS
**	-
**	RETURN VALUES
**	-
*/
void	free_prompt_line(void)
{
	free(g_data.prompt_line);
	g_data.prompt_line = NULL;
	if (g_data.cmd_path != NULL)
	{
		free(g_data.cmd_path);
		g_data.cmd_path = NULL;
	}
}

/*	GET_LOGIN
**	------------
**	DESCRIPTION
**	Concatenates the values ​​of the USER and HOSTNAME variables.
**	PARAMETERS
**	-
**	RETURN VALUES
**	Returns the login name (user@hostname) as a string
*/
char	*get_login(void)
{
	char	*user;
	char	*hostname;

	user = ft_strcat(getenv("USER"), "@");
	if (getenv("HOSTNAME") != NULL)
		hostname = ft_strdup(getenv("HOSTNAME"));
	else if (getenv("NAME") != NULL)
		hostname = ft_strdup(getenv("NAME"));
	else
		hostname = ft_strdup("minishell");
	return (colored_login(&user, &hostname));
}

/*	GET_PROMPT_LINE
**	------------
**	DESCRIPTION
**	Concatenates the values ​​of the login and cwd variables.
**	PARAMETERS
**	-
**	RETURN VALUES
**	Returns the prompt line (user@hostname:cwd$ ) as a string
*/
char	*get_prompt_line(void)
{
	char	*login;

	login = get_login();
	return (colored_prompt_line(&login));
}

/*	GET_PROMPT
**	------------
**	DESCRIPTION
**	Create prompt and save history from command line.
**	PARAMETERS
**	-
**	RETURN VALUES
**	-
*/
void	get_prompt(void)
{
	g_data.prompt_line = get_prompt_line();
	g_data.cmd_line = readline(g_data.prompt_line);
	if (g_data.cmd_line == NULL)
	{
		free_prompt_line();
		free_env_lst(&g_data.head_env);
		clear_minishell();
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else if (*g_data.cmd_line)
		add_history(g_data.cmd_line);
	free_prompt_line();
}
