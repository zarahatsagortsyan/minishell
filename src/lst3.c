/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:41:46 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:41:52 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	lst_delone(t_env *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->name);
		del(lst->value);
		free (lst);
	}
}

void	lst_delone_token(t_token *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->value);
		del(lst->quote);
		free (lst);
	}
}

t_token	*lst_new_elem_token(char type, char *value)
{
	t_token	*new_elem;

	new_elem = (t_token *)malloc(sizeof(t_token));
	if (!new_elem)
		return (0);
	new_elem->type = type;
	new_elem->value = value;
	new_elem->quote = (char *)ft_calloc(sizeof(char), (ft_strlen(value) + 1));
	new_elem->quote[sizeof(char) * ft_strlen(value)] = '\0';
	new_elem->next = 0;
	return (new_elem);
}
