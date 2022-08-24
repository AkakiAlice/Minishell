/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:51:33 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/24 16:59:09 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_double_single_quotes(char *str)
{
	int	i;

	i = 0;
	while (*str++ == '\'')
		i++;
	if (i % 2 == 0)
		return (1);
	return (0);
}

char	*get_var_value_expand(t_env *env_list, char *var)
{
	t_env	*ptr;

	ptr = env_list;
	while (ptr->next != env_list)
	{
		if (ft_strncmp(var, ptr->name, 4) == 0)
			return (ptr->value);
		ptr = ptr->next;
	}
	if (ft_strncmp(var, ptr->name, 4) == 0)
		return (ptr->value);
	return (ft_strdup(""));
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

void	is_dolar(char *str, t_data *data)
{
	char	*aux;

	if (!ft_strncmp_eq(str, "$?", 2))
	{
		aux = expand_env(str, data);
		free(str);
		str = ft_strdup(aux);
	}
	put_exit_code(str, data);
}

void	expand(t_data *data)
{
	t_cmdtable	*temp;
	int			i;

	temp = data->head_cmd;
	while (temp)
	{
		i = 0;
		while (temp->word[i])
		{
			if (ft_strncmp_eq(temp->word[i], "\"", 1)
				|| is_double_single_quotes(temp->word[i]) == 1)
				temp->word[i] = str_without_quotes(temp->word[i]);
			if (ft_strncmp_eq(temp->word[i], "$", 1))
				is_dolar(temp->word[i], data);
			if (is_double_single_quotes(temp->word[i]) == 0)
				temp->word[i] = str_without_quotes(temp->word[i]);
			i++;
		}
		temp = temp->next;
	}
}
