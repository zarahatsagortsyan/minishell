/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:44:26 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:44:27 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	parsing_ins(t_token **tokens, t_command *command, t_env **env_lst)
{
	int	fd;

	(void)tokens;
	if (ft_strncmp(command->oper, "<", 2) == 0)
	{
		fd = open(command->oper_value, O_RDONLY);
		if (fd < 0)
			return (-1);
		if (command->std_in != 0)
			close(command->std_in);
		command->std_in = fd;
	}
	else if (ft_strncmp(command->oper, "<<", 3) == 0)
		return (heredoc(command, env_lst));
	return (0);
}

static void	parsing_out(t_command *command)
{
	int	fd;

	fd = open(command->oper_value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (command->std_out != 1)
		close(command->std_out);
	command->std_out = fd;
}

static int	parsing_redirs(t_token **tokens, t_command *command, \
		t_token **tmp, t_env **env_lst)
{
	int	fd;

	if (command->oper_value != 0)
		free(command->oper_value);
	command->oper_value = ft_strdup((*tokens)->value);
	command->delimitor = (*tokens)->type;
	*tmp = *tokens;
	*tokens = (*tokens)->next;
	lst_delone_token(*tmp, &free);
	if (ft_strncmp(command->oper, ">", 2) == 0)
	{
		fd = open(command->oper_value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (command->std_out != 1)
			close(command->std_out);
		command->std_out = fd;
	}
	else if (ft_strncmp(command->oper, ">>", 3) == 0)
		parsing_out(command);
	else
		return (parsing_ins(tokens, command, env_lst));
	return (0);
}

int	parsing_operators(t_token **tokens, t_command *command, t_env **env_lst)
{
	t_token	*tmp;
	int		status;

	status = 0;
	while ((*tokens) != 0 && (*tokens)->type != 'c' && status >= 0)
	{
		if (command->oper != 0)
			free(command->oper);
		command->oper = ft_strdup((*tokens)->value);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		lst_delone_token(tmp, &free);
		if (*tokens != 0 && ((*tokens)->type == 'v' || \
					(*tokens)->type == 'h' || (*tokens)->type == 'H'))
			status = parsing_redirs(tokens, command, &tmp, env_lst);
		else
		{
			ft_putstr_fd("Minishell$ Syntax error: Undefined value after " \
					"operator\n", 2);
			return (-2);
		}
	}
	return (status);
}
