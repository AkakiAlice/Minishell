/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:51:33 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/10 16:19:17 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	EXPAND_ENV
**	------------
**	DESCRIPTION
**	Parses the variable name and finds its value.
**	PARAMETERS
**	#1. The name of the variable to expand (word);
**	RETURN VALUES
**	-
*/
char	*expand_env(char *word)
{
	char	**temp;
	char	*value;

	value = NULL;
	if (!ft_strncmp_eq(word, "$?", 2))
	{
		temp = ft_split2(word, '$');
		value = search_env_value(temp[0]);
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
**	RETURN VALUES
**	-
*/
void	is_dollar(char **str)
{
	char	*aux;
	char	*exit_code;

	if (dont_expand(*str))
		return ;
	if (!ft_strncmp_eq(*str, "$?", 2))
	{
		aux = expand_env(*str);
		free(*str);
		if (aux == NULL)
			*str = ft_strdup("");
		else
			*str = ft_strdup(aux);
	}
	if (ft_strncmp_eq(*str, "$?", 2))
	{
		if (ft_strlen(*str) > 2)
		{
			aux = ft_substr(*str, 2, ft_strlen(*str) - 2);
			exit_code = ft_itoa(g_data.status);
			free(*str);
			*str = ft_strcat(exit_code, aux);
			free(aux);
			free(exit_code);
		}
		else
		{
			free(*str);
			*str = ft_itoa(g_data.status);
		}
	}
}

void	strcat_space(char **result, char *str, bool space)
{
	char	*aux;

	aux = ft_strdup(*result);
	free(*result);
	*result = ft_strcat(aux, str);
	free(aux);
	if (space)
	{
		aux = ft_strdup(*result);
		free(*result);
		*result = ft_strcat(aux, " ");
		free(aux);
	}
}

void	test_expand(char **str)
{
	char	**split;
	char	*aux;
	char	*aux2;
	char	*aux3;
	int		i;
	char	*result;
	char	*find_dollar;
	int		diff;
	char	*exit_code;
	bool	space;

	split = ft_split(*str, ' ');
	i = 0;
	result = NULL;
	space = false;
	while (split[i])
	{
		if (split[i + 1] == NULL)
			space = false;
		else
			space = true;
		find_dollar = ft_strchr(split[i], '$');
		if (find_dollar == NULL)
		{
			if (result != NULL)
			{
				strcat_space(&result, split[i], space);
			}
			else
			{
				if (space)
					result = ft_strcat(split[i], " ");
				else
					result = ft_strdup(split[i]);
			}
		}
		else
		{
			diff = find_dollar - split[i];
			if (diff)
			{
				if (result)
				{
					aux = ft_substr(split[i], 0, diff);
					aux2 = ft_strdup(result);
					free(result);
					result = ft_strcat(aux2, aux);
					free(aux);
					free(aux2);
				}
				else
					result = ft_substr(split[i], 0, diff);
			}
			if (!find_dollar[1])
			{
				if (result)
					strcat_space(&result, split[i], space);
				else
				{
					if (space)
						result = ft_strcat(split[i], " ");
					else
						result = ft_strdup(split[i]);
				}
			}
			else if (find_dollar[1] == '?')
			{
				exit_code = ft_itoa(g_data.status);
				if (ft_strlen(find_dollar) > 2)
				{
					aux = ft_substr(find_dollar, 2, ft_strlen(find_dollar) - 2);
					if (result)
					{
						aux3 = ft_strcat(exit_code, aux);
						aux2 = ft_strdup(result);
						free(result);
						result = ft_strcat(aux2, aux3);
						free(aux2);
						free(aux3);
					}
					else
					{
						result = ft_strcat(exit_code, aux);
						if (space)
						{
							aux2 = ft_strdup(result);
							free(result);
							result = ft_strcat(aux2, " ");
							free(aux2);
						}
					}
					free(aux);
				}
				else
				{
					if (result)
						strcat_space(&result, exit_code, space);
					else
					{
						result = ft_itoa(g_data.status);
						if (space)
						{
							aux2 = ft_strdup(result);
							free(result);
							result = ft_strcat(aux2, " ");
							free(aux2);
						}
					}
				}
				free(exit_code);
			}
			else
			{
				aux = expand_env(find_dollar);
				if (result)
				{
					if (aux != NULL)
						strcat_space(&result, aux, space);
				}
				else
				{
					if (aux == NULL)
						result = ft_strdup("");
					else
						result = ft_strdup(aux);
					if (space)
					{
						aux2 = ft_strdup(result);
						free(result);
						result = ft_strcat(aux2, " ");
						free(aux2);
					}
				}
			}
		}
		i++;
	}
	free(*str);
	*str = result;
	ft_matrix_free(&split);
}

/*	PARSE_EXPANSION
**	------------
**	DESCRIPTION
**	Loops through the array and checks if there are any variables to expand.
**	PARAMETERS
**	#1. The array of char "word" (word);
**	RETURN VALUES
**	-
*/
void	parse_expansion(char **word)
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
			// if (ft_strncmp_eq(word[i], "$", 1))
			// 	is_dollar(&word[i]);
			// else
			if (!ft_strncmp_eq(word[i], "\'", 1))
				test_expand(&word[i]);
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
**	-
**	RETURN VALUES
**	-
*/
void	expand(void)
{
	t_cmdtable	*temp;

	temp = g_data.head_cmd;
	while (temp != NULL)
	{
		if (temp->redirect)
			parse_expansion(temp->redirect);
		if (temp->word)
			parse_expansion(temp->word);
		temp = temp->next;
	}
}
