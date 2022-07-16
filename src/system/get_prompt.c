/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:23:48 by alida-si          #+#    #+#             */
/*   Updated: 2022/07/16 16:44:20 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(void)
{
	char	*temp;
	char	*temp2;
	char	*name;

	temp = ft_strcat(getenv("USER"), "@");
	if (getenv("HOSTNAME") != NULL)
		temp2 = ft_strcat(getenv("HOSTNAME"), ":");
	else if (getenv("NAME") != NULL)
		temp2 = ft_strcat(getenv("NAME"), ":");
	else if (getenv("HOSTNAME") == NULL && getenv("NAME") == NULL)
		temp2 = ft_strdup("minishell:");
	name = ft_strcat(temp, temp2);
	free(temp);
	free(temp2);
	return (name);
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
void	get_prompt(t_data *data)
{
	char	*cwd;
	char	aux[1024];
	char	*name;
	char	*prompt_line;

	name = get_name();
	getcwd(aux, sizeof(aux));
	cwd = ft_strcat(aux, "$ ");
	prompt_line = ft_strcat(name, cwd);
	data->cmd_line = readline(prompt_line);
	if (*data->cmd_line)
	{
		add_history(data->cmd_line);
		free(cwd);
		free(prompt_line);
	}
	else
	{
		free(cwd);
		free(name);
		free(prompt_line);
		free(data->cmd_line);
		exit(0);
	}
}
