/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:50:05 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:50:33 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	quote_removal(t_token *tokens)
{
	int		i;
	char	*new_value;
	char	*new_quote;

	i = -1;
	while (tokens->value[++i] != '\0')
	{
		if ((tokens->value[i] == '\'' || tokens->value[i] == '\"') && \
				tokens->quote[i] == '1')
		{
			tokens->value[i] = '\0';
			new_value = ft_strjoin(tokens->value, tokens->value + i + 1);
			free(tokens->value);
			tokens->value = new_value;
			tokens->quote[i] = '\0';
			new_quote = ft_strjoin(tokens->quote, tokens->quote + i + 1);
			free(tokens->quote);
			tokens->quote = new_quote;
			--i;
			if (tokens->type == 'h')
				tokens->type = 'H';
		}
	}
}

void	change_status(t_env **env_lst, int status)
{
	t_env	*tmp;

	tmp = *env_lst;
	while (tmp->meaning != '?')
		tmp = tmp->next;
	tmp->status = status;
	if (tmp->value != 0)
		free(tmp->value);
	tmp->value = ft_itoa(tmp->status);
}

static void	dups_outs(t_command *tmp)
{
	if (tmp->std_out != 1)
	{
		tmp->std_out_dup1 = dup(1);
		dup2(tmp->std_out, 1);
		close(tmp->std_out);
		if (tmp->pipe_out != 0)
			close(tmp->pipe_out);
	}
	else if (tmp->pipe_out != 0)
	{
		tmp->std_out_dup1 = dup(1);
		dup2(tmp->pipe_out, 1);
		close(tmp->pipe_out);
	}
}

void	dups(t_command *tmp)
{
	if (tmp->std_in != 0)
	{
		tmp->std_in_dup1 = dup(0);
		dup2(tmp->std_in, 0);
		close(tmp->std_in);
		if (tmp->pipe_in != 0)
			close(tmp->pipe_in);
	}
	else if (tmp->pipe_in != 0)
	{
		tmp->std_in_dup1 = dup(0);
		dup2(tmp->pipe_in, 0);
		close(tmp->pipe_in);
	}
	dups_outs(tmp);
}

void	command_free(t_command *command)
{
	int	i;

	i = -1;
	if (command != 0)
	{
		if (command->args != 0)
		{
			while (command->args[++i] != 0)
				free(command->args[i]);
			free(command->args);
		}
		if (command->path != 0)
			free(command->path);
		if (command->oper != 0)
			free(command->oper);
		if (command->oper_value != 0)
			free(command->oper_value);
		free(command);
	}
}
