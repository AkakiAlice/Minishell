/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:51:33 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/26 21:47:10 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	expand(t_data *data)
{
	t_cmdtable	*temp;
	int			i;

	temp = data->head_cmd;
	while (temp != NULL)
	{
		i = 0;
		while (temp->word[i])
		{
			if (ft_strncmp_eq(temp->word[i], "\"", 1))
				clean_quotes(&temp->word[i], '\"');
			if (is_double_single_quotes(temp->word[i]) == 1)
				clean_quotes(&temp->word[i], '\'');
			if (ft_strncmp_eq(temp->word[i], "$", 1))
				is_dollar(&temp->word[i], data);
			if (is_double_single_quotes(temp->word[i]) == 0)
				clean_quotes(&temp->word[i], '\'');
			i++;
		}
		temp = temp->next;
	}
}
