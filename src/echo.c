/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:14:42 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 17:14:43 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_flag(char *str, int *n)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (i == 0 && str[i] == '-')
			continue ;
		else if (i != 0 && str[i] == 'n')
			continue ;
		else
			break ;
	}
	if (i != 0 && str[i] == '\0')
	{
		*n = 1;
		return (1);
	}
	return (0);
}

static void	echo_print(t_command *command, int *i)
{
	int	flag;

	flag = 0;
	while (command->args[*i] != 0)
	{
		if (flag == 1)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(command->args[*i], 1);
		flag = 1;
		++(*i);
	}
}

int	echo(t_command *command, t_env **env_lst)
{
	int	n;
	int	i;

	n = 0;
	if (command->args[1] == 0)
		ft_putchar_fd('\n', 1);
	else
	{
		i = 0;
		while (command->args[++i] != 0 && check_flag(command->args[i], &n) == 1)
			;
		echo_print(command, &i);
		if (n == 0)
			ft_putchar_fd('\n', 1);
	}
	change_status(env_lst, 0);
	return (0);
}
