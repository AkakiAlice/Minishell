/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 06:09:46 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/07/21 06:48:51 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# define SUCCESS 0
# define FAILURE 1

# define PIPE 124
# define INPUT 60
# define HEREDOC 6060
# define TRUNC 62
# define APPEND 6262
# define WORD 42
# define S_QUOTE 39
# define D_QUOTE 34

# define TOO_MANY_ARG "too many arguments"
# define UNCLOSED_QUOTES "unclosed quotes"
# define SYNTAX_ERR_PIPE "syntax error near unexpected token `|'"
# define SYNTAX_ERR_NEWLINE "syntax error near unexpected token `newline'"

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

typedef struct s_quotes
{
	int		type;
	bool	in;
}	t_quotes;

typedef struct s_data
{
	char	*cmd_line;
	char	**splited_cmdl;
}	t_data;

void	save_env(t_env **env, char **envp);
int		env_lst_add_back(t_env **last_env, char *name, char *value);
char	*get_env_value(char *envp, char *env_key);
void	get_prompt(t_data *data);
void	tokenizer(t_data *data);
void	free_env_lst(t_env **last_env);

void	lexer(t_token **last_token, char **cmd);
int		token_lst_add_back(t_token **last_token, int value);
void	free_token_lst(t_token **last_token);
int		parser(t_token *last_token);

void	put_msg(char *title, char *msg, int fd);
char	*remove_spaces_around_str(char *str);

int		save_var(t_env **last_var, char *cmd);
bool	validate_var(char *var_name, char *var_value);
bool	is_variable(char *cmd);
int		free_variable(char **var_value, char **cmd, char ***split, int status);

int		is_quote_type(char ch);
bool	validate_quote_closed(char *var_value);
bool	validate_quote_space(char *var_value);
char	*str_without_quotes(char *str);
bool	check_var_expansion(char *var_value);

void	error_msg_exit(char *title, char *msg, int fd);

#endif
