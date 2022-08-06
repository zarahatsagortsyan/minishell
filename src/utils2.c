/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:51:06 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:51:07 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*strjoin_base(char const *s1, char const *s2, char c)
{
	char			*newstr;
	size_t			i;
	size_t			j;

	newstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (!newstr)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	newstr[i] = c;
	j = 0;
	while (s2[j] != '\0')
	{
		newstr[i + 1 + j] = s2[j];
		j++;
	}
	newstr[i + j + 1] = '\0';
	return (newstr);
}

void	arr_free(char **arr)
{
	int	i;

	i = -1;
	if (arr != 0)
	{
		while (arr[++i] != 0)
			free(arr[i]);
		free(arr);
	}
}

static void	print_error(char *str)
{
	char	*tmp;
	char	*err;

	tmp = ft_strjoin(str, "': not a valid identifier\n");
	err = ft_strjoin("Minishell: '", tmp);
	free(tmp);
	ft_putstr_fd(err, 2);
	free(err);
}

int	check_var_name(char *str, int *res, t_env **env_lst)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (i == 0 && ((str[0] == '_') || (str[0] >= 'a' && str[0] <= 'z') || \
				(str[0] >= 'A' && str[0] <= 'Z')))
			continue ;
		else if (i != 0 && ((str[i] >= 48 && str[i] <= 57) || \
				(str[i] >= 'a' && str[i] <= 'z') || \
				(str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_')))
			continue ;
		else
		{
			print_error(str);
			change_status(env_lst, 1);
			*res = 1;
			return (1);
		}
	}
	return (0);
}
