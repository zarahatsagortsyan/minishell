/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:41:37 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:41:38 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*lst_last(t_env *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (0);
}

t_token	*lst_last_token(t_token *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (0);
}

void	lst_clear(t_env **lst, void (*del)(void *))
{
	t_env	*tmp;

	if (lst != 0 && *lst != 0)
	{
		while (*lst != 0)
		{
			tmp = (*lst)->next;
			lst_delone(*lst, del);
			*lst = tmp;
		}
	}
}

void	lst_clear_token(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	if (lst != 0 && *lst != 0)
	{
		while (*lst != 0)
		{
			tmp = (*lst)->next;
			lst_delone_token(*lst, del);
			*lst = tmp;
		}
	}
}
