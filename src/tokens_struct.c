/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:48:36 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:48:40 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	cmd_init(t_command **command)
{
	(*command) = (t_command *)malloc(sizeof(t_command));
	(*command)->id = 0;
	(*command)->args = 0;
	(*command)->oper = 0;
	(*command)->path = 0;
	(*command)->path_error = 0;
	(*command)->oper_value = 0;
	(*command)->builtin = 0;
	(*command)->std_in = 0;
	(*command)->std_out = 1;
	(*command)->std_err = 2;
	(*command)->pipe = 0;
	(*command)->pipe_out = 0;
	(*command)->pipe_in = 0;
	(*command)->next = 0;
}

static int	parsing_pipe(t_token **tokens, t_command *last)
{
	t_token		*tmp;
	t_command	*new_command;
	int			fd[2];

	last->pipe = 1;
	tmp = *tokens;
	*tokens = (*tokens)->next;
	lst_delone_token(tmp, &free);
	if (pipe(fd) == -1)
		return (-1);
	cmd_init(&new_command);
	last->next = new_command;
	last->pipe_out = fd[1];
	last->next->pipe_in = fd[0];
	return (0);
}

int	tokens_to_struct(t_token **tokens, t_command **command, t_env **env_lst)
{
	t_command	*last;
	int			id;

	id = 0;
	cmd_init(command);
	if (parsing_command(tokens, *command, env_lst) == -1)
		return (-1);
	(*command)->id = id;
	while ((*tokens) != 0 && ft_strncmp((*tokens)->value, "|", 2) == 0)
	{
		last = *command;
		while (last->next != 0)
			last = last->next;
		parsing_pipe(tokens, last);
		last = *command;
		while (last->next != 0)
			last = last->next;
		if (parsing_command(tokens, last, env_lst) == -1)
			return (-1);
		last->id = ++id;
	}
	return (0);
}
