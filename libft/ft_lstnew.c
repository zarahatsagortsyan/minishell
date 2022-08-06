/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:49:10 by salaverd          #+#    #+#             */
/*   Updated: 2022/05/13 19:01:11 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*arr_list;

	arr_list = (t_list *)malloc(sizeof(t_list) * 1);
	if (!arr_list)
		return (NULL);
	arr_list->content = content;
	arr_list->next = NULL;
	return (arr_list);
}
