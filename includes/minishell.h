/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 06:09:46 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/13 17:04:31 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>

# define SUCCESS 0
# define FAILURE 1

# define SPC 32
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
# define IS_DIR "Is a directory"
# define NO_FILE_DIR "No such file or directory"
# define CMD_NOT_FOUND "command not found"

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

typedef struct s_split
{
	char	**words;
	int		num_word;
}	t_split;

typedef struct s_cmdtable
{
	char				**word;
	int					fdin;
	int					fdout;
	struct s_cmdtable	*next;
}	t_cmdtable;

typedef struct s_data
{
	t_token		*last_token;
	t_env		*last_env;
	t_cmdtable	*head_cmd;
	char		*cmd_line;
	char		*env_value;
	char		*cmd_path;
	char		**splited_cmdl;
	char		*prompt_line;
	char		*path_value;
	int			status;
}	t_data;

void	builtin(t_data *data);
void	exit_cmd(t_data *data);

void	create_cmd_table(t_data *data);
void	cmd_lst_add_front(t_cmdtable **head_cmd, char *pipe_line);
void	free_cmd_lst(t_cmdtable **head_cmd);

void	check_cmd(t_data *data);
void	fork_it(t_data *data, t_env **last_env);
void	exec_cmd(t_data *data, t_env **last_env, char **word);
char	*get_path(t_env *env_list);

void	save_env(t_env **env, char **envp);
int		env_lst_add_back(t_env **last_env, char *name, char *value);
char	*get_env_value(char *envp, char *env_key);
void	get_prompt(t_data *data, t_env **last_env);
void	free_env_lst(t_env **last_env);

void	lexer(t_token **last_token, char **cmd);
int		token_lst_add_back(t_token **last_token, int value);
void	free_token_lst(t_token **last_token);
void	tokenizer(t_data *data);
int		parser(t_data *data);
int		syntax_error(t_data *data, char *msg);
int		count_cmd_words(char *cmd);
int		is_reserved_word(char c);
void	skip_char(char **str, char ch);
bool	check_reserved_word(char **cmd, int *word_count, bool is_word);
int		find_first_reserved_char(char *cmd);
void	save_word_with_quotes(t_split *split, char **cmd, int *i);
void	save_reserved_word(t_split *split, char **cmd, int *i);

void	put_msg(char *title, char *msg, int fd);
char	*remove_spaces_around_str(char *str);
char	*remove_spaces_outside_quote(char *str);
void	free_minishell(t_data *data);
void	minishell_init(t_data *data);
char	**split_cmd(char *cmd);

int		save_var(t_env **last_var, char *cmd);
bool	validate_var(char *var_name, char *var_value);
bool	is_variable(char *cmd);
int		free_variable(char **var_value, char **cmd, char ***split, int status);

int		is_quote_type(char ch);
bool	validate_quote_closed(char *var_value);
bool	validate_quote_space(char *var_value);
char	*str_without_quotes(char *str);
bool	check_var_expansion(char *var_value);
void	skip_quotes(char **cmd);

void	error_msg_exit(char *title, char *msg, int fd);

#endif
