/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 06:09:46 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/06/29 07:39:55 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

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

void	save_env(t_env **env, char **envp);
int		env_lst_add_back(t_env **last_env, char *name, char *value);
char	*get_env_value(char *envp, char *env_key);
void	free_env_lst(t_env **last_env);

void	lexer(t_token **last_token, char **cmd);
int		token_lst_add_back(t_token **last_token, int value);
void	free_token_lst(t_token **last_token);

int	ft_strncmp_eq(char *s1, char *s2, size_t n);

#endif
