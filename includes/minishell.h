/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 06:09:46 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/15 15:47:21 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>

# define SUCCESS 0
# define FAILURE 1

# define PIPE 0
# define INPUT 1
# define HEREDOC 2
# define TRUNC 3
# define APPEND 4
# define WORD 5

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}		t_env;

typedef struct s_token
{
	int				value;
	struct s_token	*next;
}		t_token;

typedef struct s_data
{
	char	*cmd_line;
	char	*env_value;
	char	*cmd_path;
	char	**splited_cmdl;
	int		status;
}	t_data;

void	save_env(t_env **env, char **envp);
int		env_lst_add_back(t_env **last_env, char *name, char *value);
char	*get_env_value(char *envp, char *env_key);
void	get_prompt(t_data *data);
void	tokenizer(t_data *data);
void	exec_cmd(t_data *data);
void	fork_it(t_data *data);
void	free_env_lst(t_env **last_env);
char	*get_path(t_env *env_list);
void	check_cmd(char *env_value, t_data *data);

void	lexer(t_token **last_token, char **cmd);
int		token_lst_add_back(t_token **last_token, int value);
void	free_token_lst(t_token **last_token);

#endif
