/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:59:33 by salaverd          #+#    #+#             */
/*   Updated: 2022/05/13 19:06:57 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_num(long n)
{
	int	i;

	i = 1;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_utoa(unsigned int n)
{
	char	*str;
	int		size;
	long	num;

	num = n;
	size = count_num(num);
	if (n == 0)
		return (str = ft_strdup("0"));
	str = malloc(sizeof(char) * size);
	if (!str)
		return (0);
	str[--size] = '\0';
	while (num / 10 >= 1)
	{
		str[--size] = (num % 10) + '0';
		num /= 10;
	}
	str[0] = (num % 10) + '0';
	return (str);
}
