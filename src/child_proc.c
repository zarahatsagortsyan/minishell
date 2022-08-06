/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:13:51 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 17:14:10 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	proc_handle_sigint(int sig)
{
	(void)sig;
	exit(2);
}

static void	proc_handle_sigquit(int sig)
{
	(void)sig;
	exit(3);
}

static t_command	*close_pipes(t_command **command, int id)
{
	t_command	*tmp;

	tmp = *command;
	while (tmp != 0)
	{
		if (tmp->id != id)
		{
			if (tmp->std_in != 0)
				close(tmp->std_in);
			if (tmp->std_out != 1)
				close(tmp->std_out);
			if (tmp->pipe_out != 0)
				close(tmp->pipe_out);
			if (tmp->pipe_in != 0)
				close(tmp->pipe_in);
		}
		tmp = tmp->next;
	}
	tmp = *command;
	while (tmp->id != id)
		tmp = tmp->next;
	dups(tmp);
	return (tmp);
}

static void	not_builtin(t_env **env_lst, t_command *exec_com)
{
	int			i;
	char		**envp;

	envp = env_lst_to_arr(*env_lst, 'e', 0);
	i = execve(exec_com->path, exec_com->args, envp);
	if (i == -1)
	{
		ft_putstr_fd("Minishell$ command not found: ", 2);
		ft_putstr_fd(exec_com->args[0], 2);
		ft_putchar_fd('\n', 2);
	}
	exit (2);
}

void	child(t_command **command, t_env **env_lst, int id)
{
	t_command	*exec_com;

	signal(SIGINT, proc_handle_sigint);
	signal(SIGQUIT, proc_handle_sigquit);
	exec_com = close_pipes(command, id);
	exec_com->path = find_command(exec_com, *env_lst);
	if (exec_com->path == 0)
	{
		if (exec_com->path_error == 0)
			exit(0);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(exec_com->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (exec_com->builtin != 1)
		not_builtin(env_lst, exec_com);
	else
		exec_builtin(exec_com, env_lst, 1);
}
