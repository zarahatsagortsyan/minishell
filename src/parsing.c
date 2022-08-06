/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:45:01 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:46:18 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clear_all(t_command **command, t_token **tokens)
{
	lst_clear_token(tokens, &free);
	while (*command != 0)
	{
		command_free(*command);
		*command = (*command)->next;
	}
}

int	parsing(char *line, t_token **tokens, t_env **env_lst)
{
	int			count;
	char		metachars[11];
	t_command	*command;

	*tokens = 0;
	command = 0;
	ft_strlcpy(metachars, "<>|&;() \t\n", 11);
	count = tokens_count(line, metachars);
	if (count > 0)
	{
		tokens_array(line, metachars, tokens);
		if (operators(*tokens) == -1)
		{
			lst_clear_token(tokens, &free);
			return (-1);
		}
		if (tokens_to_struct(tokens, &command, env_lst) == 0)
			exec(&command, env_lst);
		clear_all(&command, tokens);
	}
	return (1);
}
