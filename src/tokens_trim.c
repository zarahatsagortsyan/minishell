/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:48:49 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:48:56 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_token	*split_into_new_elem(char *str, t_token *tmp)
{
	t_token	*new_elem;

	new_elem = lst_new_elem_token('o', str);
	new_elem->next = tmp->next;
	return (new_elem);
}

static void	tokens_split(t_token **tokens)
{
	t_token	*tmp;
	char	**arr;
	int		i;

	tmp = *tokens;
	i = -1;
	while (tmp != 0)
	{
		if (tmp->type == 'o' && (ft_strchr(tmp->value, ' ') != 0))
		{
			arr = ft_split(tmp->value, ' ');
			tmp->type = 'd';
			while (arr[++i] != 0)
			{
				tmp->next = split_into_new_elem(arr[i], tmp);
				tmp = tmp->next;
			}
			if (arr != 0)
				free(arr);
		}
		tmp = tmp->next;
	}
}

static void	tokens_value_trim(t_token *tokens)
{
	char	*str;

	while (tokens != 0)
	{
		str = ft_strtrim(tokens->value, " ");
		free(tokens->value);
		tokens->value = str;
		tokens = tokens->next;
	}
}

void	tokens_trim(t_token **tokens)
{
	t_token	*tmp1;
	t_token	*tmp2;

	tmp1 = *tokens;
	tokens_value_trim(*tokens);
	tokens_split(tokens);
	while (tmp1 != 0)
	{
		if (((ft_strlen(tmp1->value) == 0) || tmp1->type == 'd') && \
				tmp1 == *tokens)
		{
			*tokens = tmp1->next;
			lst_delone_token(tmp1, &free);
			tmp1 = *tokens;
		}
		else if ((tmp1->next != 0) && ((ft_strlen(tmp1->next->value) == 0) || \
				tmp1->next->type == 'd'))
		{
			tmp2 = tmp1->next;
			tmp1->next = tmp1->next->next;
			lst_delone_token(tmp2, &free);
		}
		else if (tmp1 != 0)
			tmp1 = tmp1->next;
	}
}
