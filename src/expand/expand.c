/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:51:33 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/30 10:55:23 by alida-si         ###   ########.fr       */
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
	while (ptr->next != NULL)
	{
		if (ft_strncmp(var, ptr->name, 4) == 0)
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

/*	EXPAND
**	------------
**	DESCRIPTION
**	Loops through the linked list of commands and checks
**	if there are any variables to expand.
**	PARAMETERS
**	#1. The pointer to struct "data" (data);
**	RETURN VALUES
**	-
*/
/*void	expand(t_data *data)
{
	t_cmdtable	*temp;
	int			i;

	temp = data->head_cmd;
	while (temp != NULL)
	{
		i = 0;
		if (temp->redirect == NULL)
		{
			while (temp->word[i])
			{
				if (is_var_expansion(temp->word[i])) {
					if (ft_strncmp_eq(temp->word[i], "\"", 1))
						clean_quotes(&temp->word[i], '\"');
					if (is_double_single_quotes(temp->word[i]) == 1)
						clean_quotes(&temp->word[i], '\'');
					if (ft_strncmp_eq(temp->word[i], "$", 1))
						is_dollar(&temp->word[i], data);
					if (is_double_single_quotes(temp->word[i]) == 0)
						clean_quotes(&temp->word[i], '\'');
				}
				i++;
			}
		}
		temp = temp->next;
	}
}*/

void	expand(char **word, t_data *data)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (is_var_expansion(word[i]))
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

void	teste(t_data *data)
{
	t_cmdtable	*temp;

	temp = data->head_cmd;
	while (temp != NULL)
	{
		if (temp->redirect)
			expand(temp->redirect, data);
		if (temp->word)
			expand(temp->word, data);
		temp = temp->next;
	}
}
