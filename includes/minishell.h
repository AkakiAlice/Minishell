/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:19:57 by alida-si          #+#    #+#             */
/*   Updated: 2022/06/25 15:43:22 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define FAILURE 1

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}		t_env;

typedef struct s_data
{
	char	*cmd_line;
	char	**splited_cmdl;
}	t_data;

void	save_env(t_env **env, char **envp);
int		env_lst_add_back(t_env **env_last, char *name, char *value);
char	*get_env_value(char *envp, char *env_key);
void	get_prompt(t_data *data);
void	free_matrix(char **ptr);
void	tokenizer(t_data *data);

#endif