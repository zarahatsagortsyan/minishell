/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:53:45 by salaverd          #+#    #+#             */
/*   Updated: 2022/05/13 19:27:28 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char sep)
{
	int	i;
	int	count;

	if (s == 0 || s[0] == 0)
		return (0);
	i = 1;
	count = 0;
	if (s[0] != sep)
		count++;
	while (s[i])
	{
		if (s[i] != sep && s[i - 1] == sep)
			count++;
		i++;
	}
	return (count);
}

static char	**ft_mmalloc(char const *s, char sep)
{
	int		len;
	char	**tab_s;

	len = ft_count(s, sep);
	tab_s = malloc(sizeof(*tab_s) * (len + 1));
	if (!tab_s)
		return (NULL);
	return (tab_s);
}

static int	ft_count_in_between(char const *s, char sep, int i)
{
	int		count;

	count = 0;
	while (s[i] && s[i] == sep)
		i++;
	while (s[i] && s[i] != sep)
	{
		count++;
		i++;
	}
	return (count);
}

static char	**ft_free(char **s_tab, int i)
{
	int	j;

	j = 0;
	while (j < i && s_tab[j])
	{
		free(s_tab[j]);
		j++;
	}
	free(s_tab);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		k;
	int		i;
	int		j;
	char	**tab_s;

	k = 0;
	i = -1;
	tab_s = ft_mmalloc(s, c);
	if (!tab_s)
		return (0);
	while (++i < ft_count(s, c))
	{
		j = 0;
		tab_s[i] = malloc(ft_count_in_between(s, c, k) + 1);
		if (!tab_s)
			return (ft_free(tab_s, i));
		while (s[k] && s[k] == c)
			k++;
		while (s[k] && s[k] != c)
			tab_s[i][j++] = s[k++];
		tab_s[i][j] = '\0';
	}
	tab_s[i] = 0;
	return (tab_s);
}
