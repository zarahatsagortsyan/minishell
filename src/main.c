/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:44:07 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:44:09 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_status(t_env *env_lst, int *status)
{
	while (env_lst->meaning != '?')
		env_lst = env_lst->next;
	if (env_lst->value != 0)
	{
		if (ft_strncmp(env_lst->value, "exit", 5) == 0)
		{
			*status = env_lst->status;
			return (1);
		}
	}
	return (0);
}

int	check_and_init(int argc, char **envp, t_env **env_lst)
{
	if (argc > 1)
	{
		ft_putstr_fd("Argument error\n", 2);
		return (EXIT_FAILURE);
	}
	signals_init();
	env_list(envp, env_lst);
	shlvl(env_lst);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*env_list;
	t_token		*tokens;
	char		*line;
	int			status;

	(void)argv;
	if (check_and_init(argc, envp, &env_list) == 1)
		return (0);
	while (true)
	{
		line = readline("Minishell: ");
		if (!line)
		{
			ft_putstr_fd("exit", 1);
			return (EXIT_SUCCESS);
		}
		if (ft_strncmp(line, "", ft_strlen(line)) != 0)
			add_history(line);
		parsing(line, &tokens, &env_list);
		free(line);
		if (check_status(env_list, &status) == 1)
			break ;
	}
	lst_clear(&env_list, &free);
	return (status);
}
