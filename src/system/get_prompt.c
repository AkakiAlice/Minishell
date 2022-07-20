/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:23:48 by alida-si          #+#    #+#             */
/*   Updated: 2022/07/20 13:50:14 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_login(void)
{
	char	*user;
	char	*hostname;
	char	*login;

	user = ft_strcat(getenv("USER"), "@");
	if (getenv("HOSTNAME") != NULL)
		hostname = ft_strcat(getenv("HOSTNAME"), ":");
	else if (getenv("NAME") != NULL)
		hostname = ft_strcat(getenv("NAME"), ":");
	else if (getenv("HOSTNAME") == NULL && getenv("NAME") == NULL)
		hostname = ft_strdup("minishell:");
	login = ft_strcat(user, hostname);
	free(user);
	free(hostname);
	return (login);
}

/*	GET_PROMPT
**	------------
**	DESCRIPTION
**	Create prompt and save history from command line.
**	PARAMETERS
**	#1. The pointer to structure that contains the command line variable (data);
**	RETURN VALUES
**	-
*/
void	get_prompt(t_data *data, t_env **last_env)
{
	char	*cwd;
	char	aux[1024];
	char	*name;
	char	*prompt_line;

	name = get_login();
	getcwd(aux, sizeof(aux));
	cwd = ft_strcat(aux, "$ ");
	prompt_line = ft_strcat(name, cwd);
	data->cmd_line = readline(prompt_line);
	if (*data->cmd_line)
	{
		add_history(data->cmd_line);
		free(cwd);
		free(prompt_line);
		free(name);
	}
	else
	{
		free(cwd);
		free(name);
		free(prompt_line);
		free_env_lst(last_env);
		free(data->cmd_line);
		if (data->cmd_path != NULL)
			free(data->cmd_path);
		exit(0);
	}
}
