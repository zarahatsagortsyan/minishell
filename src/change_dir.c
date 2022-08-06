/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:12:35 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 17:13:26 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*getold(t_env **env_lst)
{
	t_env	*tmp;

	tmp = *env_lst;
	while (tmp != 0)
	{
		if (ft_strncmp(tmp->name, "PWD", 4) == 0 && tmp->meaning != 'p')
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (0);
}

static void	change_env(char *oldpwd, t_env *env_lst)
{
	while (env_lst != 0)
	{
		if (ft_strncmp(env_lst->name, "PWD", 4) == 0)
		{
			free(env_lst->value);
			env_lst->value = getcwd(NULL, 0);
		}
		else if (ft_strncmp(env_lst->name, "OLDPWD", 7) == 0)
		{
			if (env_lst->value != 0)
				free(env_lst->value);
			if (oldpwd == 0)
			{
				env_lst->value = ft_strdup("");
				env_lst->meaning = 'q';
			}
			else
				env_lst->value = ft_strdup(oldpwd);
		}
		env_lst = env_lst->next;
	}
}

static int	cd_parent(char *path, t_env **env_lst, char *oldpwd)
{
	int		exit_status;

	wait(&exit_status);
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	if (exit_status == 0 && chdir(path) == 0)
	{
		change_env(oldpwd, *env_lst);
		free(path);
		change_status(env_lst, 0);
		return (0);
	}
	if (exit_status != 0)
		ft_putstr_fd("cd: error retrieving current directory: getcwd: " \
				"cannot access parent directories: No such file or " \
				"directory\n", 2);
	else
		perror(path);
	free(path);
	if (oldpwd != 0)
		free(oldpwd);
	change_status(env_lst, 1);
	return (2);
}

int	change_dir(char *path, t_env **env_lst)
{
	char	*oldpwd;
	int		pid;

	oldpwd = getold(env_lst);
	pid = fork();
	if (pid == 0)
	{
		if (chdir(path) == 0 && getcwd(NULL, 0) == NULL)
			exit(1);
		exit(0);
	}
	else
		return (cd_parent(path, env_lst, oldpwd));
}
