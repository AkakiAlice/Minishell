/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:51:33 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/06 17:44:40 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	GET_VAR_VALUE_EXPAND
**	------------
**	DESCRIPTION
**	Loops through the linked list of environment variables
**	until it finds the value corresponding to the received argument.
**	PARAMETERS
**	#1. The linked list of environment variables (env_list);
**	#2. The name of the variable to look for (var);
**	RETURN VALUES
**	The value of the environment variable
*/
char	*get_var_value_expand(t_env *env_list, char *var)
{
	t_env	*ptr;

	ptr = env_list;
	while (ptr != NULL)
	{
		if (strcmp_eq(var, ptr->name))
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}

/*	EXPAND_ENV
**	------------
**	DESCRIPTION
**	Parses the variable name and finds its value.
**	PARAMETERS
**	#1. The name of the variable to expand (word);
**	#2. The pointer to struct "data" (data);
**	RETURN VALUES
**	-
*/
char	*expand_env(char *word, t_data *data)
{
	char	**temp;
	char	*value;

	if (!ft_strncmp_eq(word, "$?", 2))
	{
		temp = ft_split2(word, '$');
		value = get_var_value_expand(data->head_env, temp[0]);
		ft_matrix_free(&temp);
	}
	return (value);
}

/*	IS_DOLLAR
**	------------
**	DESCRIPTION
**	Replace the variable name with its value.
**	PARAMETERS
**	#1. The name of the variable to expand (str);
**	#2. The pointer to struct "data" (data);
**	RETURN VALUES
**	-
*/
void	is_dollar(char **str, t_data *data)
{
	char	*aux;

	if (dont_expand(*str))
		return ;
	if (!ft_strncmp_eq(*str, "$?", 2))
	{
		aux = expand_env(*str, data);
		free(*str);
		if (aux == NULL)
			*str = ft_strdup("");
		else
			*str = ft_strdup(aux);
	}
	if (ft_strncmp_eq(*str, "$?", 2))
	{
		free(*str);
		*str = ft_itoa(data->status);
	}
}

/*	PARSE_EXPANSION
**	------------
**	DESCRIPTION
**	Loops through the array and checks if there are any variables to expand.
**	PARAMETERS
**	#1. The array of char "word" (word);
**	#2. The pointer to struct "data" (data);
**	RETURN VALUES
**	-
*/
void	parse_expansion(char **word, t_data *data)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (is_var_expansion(word[i]) && (get_token(word[i - 1]) != HEREDOC))
		{
			if (ft_strncmp_eq(word[i], "\"", 1))
				clean_quotes(&word[i], '\"');
			if (is_double_single_quotes(word[i]) == 1)
				clean_quotes(&word[i], '\'');
			if (ft_strncmp_eq(word[i], "$", 1))
				is_dollar(&word[i], data);
			if (is_double_single_quotes(word[i]) == 0)
				clean_quotes(&word[i], '\'');
		}
		i++;
	}
}

/*	EXPAND
**	------------
**	DESCRIPTION
**	Loops through the linked list and call the "parse_expression" function
**	in case of redirections and words.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	RETURN VALUES
**	-
*/
void	expand(t_data *data)
{
	t_cmdtable	*temp;

	temp = data->head_cmd;
	while (temp != NULL)
	{
		if (temp->redirect)
			parse_expansion(temp->redirect, data);
		if (temp->word)
			parse_expansion(temp->word, data);
		temp = temp->next;
	}
}
