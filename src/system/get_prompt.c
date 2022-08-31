/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:23:48 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/31 07:57:48 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	FREE_PROMPT_LINE
**	------------
**	DESCRIPTION
**	Frees the pointers that make up the command line.
**	PARAMETERS
**	#1. The pointer to the current working directory string (cwd);
**	#2. The pointer to the login name (user@hostname) (login);
**	#3. The pointer to the prompt line (prompt_line);
**	RETURN VALUES
**	-
*/
void	free_prompt_line(t_data *data)
{
	free(data->prompt_line);
	data->prompt_line = NULL;
	if (data->cmd_path != NULL)
	{
		free(data->cmd_path);
		data->cmd_path = NULL;
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
	char	*login;

	user = ft_strcat(getenv("USER"), "@");
	if (getenv("HOSTNAME") != NULL)
		hostname = ft_strcat(getenv("HOSTNAME"), ":");
	else if (getenv("NAME") != NULL)
		hostname = ft_strcat(getenv("NAME"), ":");
	else
		hostname = ft_strdup("minishell:");
	login = ft_strcat(user, hostname);
	free(user);
	free(hostname);
	return (login);
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
	char	*cwd;
	char	aux[1024];
	char	*login;
	char	*prompt_line;

	login = get_login();
	getcwd(aux, sizeof(aux));
	cwd = ft_strcat(aux, "$ ");
	prompt_line = ft_strcat(login, cwd);
	free(cwd);
	free(login);
	return (prompt_line);
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
void	get_prompt(t_data *data, t_env **head_env)
{
	data->prompt_line = get_prompt_line();
	data->cmd_line = readline(data->prompt_line);
	if (data->cmd_line == NULL)
	{
		free_prompt_line(data);
		free_env_lst(head_env);
		clear_minishell();
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else if (*data->cmd_line)
		add_history(data->cmd_line);
	free_prompt_line(data);
}
