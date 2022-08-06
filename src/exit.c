/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:39:52 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:39:54 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exit_status_correct(long res)
{
	long double	num;
	long		int_part;

	if (res >= 0 && res <= 255)
		return (res);
	num = (long double)res / 256;
	int_part = (long)num;
	num = (num - int_part) * 256;
	if (num >= ((long)num + 0.5))
		res = (long)num + 1;
	else
		res = (long)num;
	if (res < 0)
		return (256 + res);
	else
		return (res);
}

static int	parsing_code(t_command *command, int *k)
{
	long	res;
	int		i;

	i = -1;
	while (command->args[1][++i] != '\0')
		if (!(ft_isdigit(command->args[1][i]) == 1 || \
				(i == 0 && command->args[1][i] == '-') || \
				(i == 0 && command->args[1][i] == '+')))
			break ;
	if (command->args[1][i] == '\0')
	{
		res = ft_atoi(command->args[1], k);
		res = exit_status_correct(res);
	}
	else
	{
		*k = 1;
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(command->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		res = 255;
	}
	return (res);
}

static void	run_exit(t_env *env_lst)
{
	while (env_lst->meaning != '?')
		env_lst = env_lst->next;
	if (env_lst->value != 0)
		free(env_lst->value);
	env_lst->value = ft_strdup("exit");
}

int	my_exit(t_command *command, t_env **env_lst)
{
	int	res;
	int	k;

	k = 0;
	if (command->args[1] != 0)
	{
		res = parsing_code(command, &k);
		if (command->args[2] == 0 && k == 0)
			ft_putstr_fd("exit\n", 1);
		if (command->args[2] != 0 && k == 0)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
			change_status(env_lst, 1);
			return (2);
		}
		change_status(env_lst, res);
		run_exit(*env_lst);
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		run_exit(*env_lst);
	}
	return (0);
}
