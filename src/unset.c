/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:49:46 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:49:50 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	find_and_del(t_command *command, t_env **env_lst, int i)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = *env_lst;
	while (tmp != 0)
	{
		if (tmp->next != 0 && ft_strncmp(command->args[i], tmp->next->name, \
					ft_strlen(command->args[i]) + 1) == 0)
		{
			tmp2 = tmp->next;
			if (tmp->next->next != 0)
				tmp->next = tmp->next->next;
			else
				tmp->next = 0;
			lst_delone(tmp2, &free);
		}
		else
			tmp = tmp->next;
	}
}

static void	pwd_imitation(t_env *env_lst)
{
	while (env_lst != 0)
	{
		if (ft_strncmp(env_lst->name, "PWD", 4) == 0)
		{
			env_lst->meaning = 'p';
			break ;
		}
		env_lst = env_lst->next;
	}
}

static void	unset_vars(t_command *command, t_env **env_lst, int *res)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (command->args[++i] != 0)
	{
		if (check_var_name(command->args[i], res, env_lst) == 0)
		{
			if (ft_strncmp(command->args[i], "PWD", 4) == 0)
				pwd_imitation(*env_lst);
			else if (ft_strncmp(command->args[i], (*env_lst)->name, \
						ft_strlen(command->args[i]) + 1) == 0)
			{
				tmp = *env_lst;
				*env_lst = (*env_lst)->next;
				lst_delone(tmp, &free);
				continue ;
			}
			else
				find_and_del(command, env_lst, i);
		}
	}
}

int	unset(t_command *command, t_env **env_lst)
{
	int	res;

	res = 0;
	if (env_lst != 0 && command != 0)
	{
		if (command->args[1] == 0)
			change_status(env_lst, 0);
		else
			unset_vars(command, env_lst, &res);
	}
	if (res == 0)
		change_status(env_lst, 0);
	else
		change_status(env_lst, 1);
	return (0);
}
