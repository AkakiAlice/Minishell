/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:51:33 by alida-si          #+#    #+#             */
/*   Updated: 2022/09/10 17:28:37 by pmitsuko         ###   ########.fr       */
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

/*	CHECK_EXPAND
**	------------
**	DESCRIPTION
**	Save prefix expand and expanded value.
**	PARAMETERS
**	#1. The result string (result);
**	#2. The string from dollar char (dollar);
**	#3. The string (str);
**	#4. The flag to include space at the end (space);
**	RETURN VALUES
**	-
*/
static void	check_expand(char **result, char *dollar, char *str, bool space)
{
	if (dollar - str)
		save_prefix(result, str, dollar - str);
	if (!dollar[1])
		save_str(result, str, space);
	else if (dollar[1] == '?')
		save_exit_code(result, dollar, space);
	else
		save_expand_env(result, dollar, space);
}

/*	EXPAND_WORD
**	------------
**	DESCRIPTION
**	Expand all variables.
**	PARAMETERS
**	#1. The string (str);
**	RETURN VALUES
**	-
*/
static void	expand_word(char **str)
{
	t_expand	exp;
	int			i;

	exp.split = ft_split(*str, ' ');
	i = 0;
	exp.result = NULL;
	exp.space = false;
	while (exp.split[i])
	{
		if (exp.split[i + 1] == NULL)
			exp.space = false;
		else
			exp.space = true;
		exp.find_dollar = ft_strchr(exp.split[i], '$');
		if (exp.find_dollar == NULL)
			save_str(&exp.result, exp.split[i], exp.space);
		else
			check_expand(&exp.result, exp.find_dollar, exp.split[i], exp.space);
		i++;
	}
	free(*str);
	*str = exp.result;
	ft_matrix_free(&exp.split);
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
			if (!ft_strncmp_eq(word[i], "\'", 1))
				expand_word(&word[i]);
			else
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
