/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:41:21 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:41:27 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*lst_new_elem(char *name, char *value)
{
	t_env	*new_elem;

	new_elem = (t_env *)malloc(sizeof(t_env));
	if (!new_elem)
		return (0);
	new_elem->name = name;
	new_elem->value = value;
	new_elem->meaning = 'e';
	new_elem->next = 0;
	return (new_elem);
}

void	lst_add_back(t_env **lst, t_env *new_node)
{
	t_env	*tmp;

	if (lst)
	{
		if (*lst == 0)
			*lst = new_node;
		else
		{
			tmp = lst_last(*lst);
			tmp->next = new_node;
		}
	}
}

void	lst_add_back_token(t_token **lst, t_token *new_node)
{
	t_token	*tmp;

	if (lst)
	{
		if (*lst == 0)
			*lst = new_node;
		else
		{
			tmp = lst_last_token(*lst);
			tmp->next = new_node;
		}
	}
}

void	lst_add_front(t_env **lst, t_env *new_elem)
{
	if (lst && new_elem)
	{
		new_elem->next = *lst;
		*lst = new_elem;
	}
}
