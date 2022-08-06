/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:46:23 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:46:28 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_from_env(t_env *env_lst)
{
	while (env_lst != 0)
	{
		if (ft_strncmp(env_lst->name, "PWD", 4) == 0)
		{
			ft_putstr_fd(env_lst->value, 1);
			ft_putchar_fd('\n', 1);
			return (1);
		}
		env_lst = env_lst->next;
	}
	return (0);
}

int	pwd(t_env **env_lst)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir == 0)
	{
		if (get_from_env(*env_lst) == 0)
		{
			errno = 127;
			change_status(env_lst, 2);
			perror("pwd");
			return (2);
		}
		return (0);
	}
	else
	{
		ft_putstr_fd(dir, 1);
		ft_putchar_fd('\n', 1);
		free(dir);
		change_status(env_lst, 0);
		return (0);
	}
}
