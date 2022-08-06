/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:46:36 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:46:38 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static long	new_atoi(const char *str, int *lvl)
{
	long			res;
	int				sign;
	unsigned int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || \
str[i] == '\n' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	*lvl = res * sign;
	if (str[i] != '\0')
		return (0);
	else
		return (1);
}

static void	lvl_up(int lvl, t_env *tmp, char *str)
{
	if (lvl < 0)
		lvl = 0;
	else if (lvl >= 0 && lvl <= 999)
		lvl++;
	else
	{
		ft_putstr_fd("Minishell: warning: shell level (", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		lvl = 1;
	}
	if (lvl == 1000)
	{
		free(tmp->value);
		tmp->value = ft_strdup("");
	}
	else
	{
		free(tmp->value);
		tmp->value = ft_itoa(lvl);
	}
}

void	shlvl(t_env **env_lst)
{
	t_env	*new_elem;
	t_env	*tmp;
	int		lvl;

	tmp = *env_lst;
	while (tmp != 0)
	{
		if (ft_strncmp(tmp->name, "SHLVL", ft_strlen(tmp->name)) == 0)
		{
			if (new_atoi(tmp->value, &lvl) == 0)
				lvl = 1;
			lvl_up(lvl, tmp, tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp == 0)
	{
		new_elem = lst_new_elem(ft_strdup("SHLVL"), ft_strdup("1"));
		lst_add_back(env_lst, new_elem);
	}
}
