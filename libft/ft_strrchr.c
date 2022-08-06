/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:57:10 by salaverd          #+#    #+#             */
/*   Updated: 2021/04/25 17:57:11 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int		i;
	char	c;
	char	*s;
	char	*res;

	i = 0;
	c = (char)ch;
	s = (char *)str;
	res = NULL;
	if (c == '\0')
		return (s + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == c)
			res = &s[i];
		i++;
	}
	return (res);
}
