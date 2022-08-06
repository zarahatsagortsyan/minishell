/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:39:16 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:39:19 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exec_run(t_command *command, t_env **env_lst)
{
	if (ft_strncmp(command->path, "pwd", 4) == 0)
		return (pwd(env_lst));
	else if (ft_strncmp(command->path, "env", 4) == 0)
		return (env(env_lst));
	else if (ft_strncmp(command->path, "unset", 6) == 0)
		return (unset(command, env_lst));
	else if (ft_strncmp(command->path, "export", 7) == 0)
		return (export_env(command, env_lst));
	else if (ft_strncmp(command->path, "echo", 5) == 0)
		return (echo(command, env_lst));
	else if (ft_strncmp(command->path, "exit", 5) == 0)
		return (my_exit(command, env_lst));
	else if (ft_strncmp(command->path, "cd", 3) == 0)
		return (cd(command, env_lst));
	return (0);
}

static void	close_dups(t_command *command)
{
	if (command->std_in != 0)
	{
		close(0);
		dup2(command->std_in_dup1, 0);
		close(command->std_in_dup1);
	}
	if (command->std_out != 1)
	{
		close(1);
		dup2(command->std_out_dup1, 1);
		close(command->std_out_dup1);
	}
}

static void	exec_run_par(t_command *command, t_env **env_lst)
{
	dups(command);
	exec_run(command, env_lst);
	close_dups(command);
}

void	exec_builtin(t_command *command, t_env **env_lst, int child_parent)
{
	if (child_parent == 0)
		exec_run_par(command, env_lst);
	else if (child_parent == 1)
		exit(exec_run(command, env_lst));
}
