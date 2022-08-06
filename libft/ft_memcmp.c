/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:51:31 by salaverd          #+#    #+#             */
/*   Updated: 2022/05/13 19:03:04 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *array_1, const void *array_2, size_t n)
{
	unsigned char	*arr_1;
	unsigned char	*arr_2;
	size_t			i;

	i = 0;
	arr_1 = (unsigned char *)array_1;
	arr_2 = (unsigned char *)array_2;
	while (i < n)
	{
		if (arr_1[i] != arr_2[i])
			return (arr_1[i] - arr_2[i]);
		i++;
	}
	return (0);
}
