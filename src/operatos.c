/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operatos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:44:39 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:44:44 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	operators(t_token *tokens)
{
	while (tokens != 0)
	{
		if (tokens->type == 'o')
		{
			if (ft_strncmp(tokens->value, ">", 2) == 0 || \
					ft_strncmp(tokens->value, ">>", 3) == 0 || \
					ft_strncmp(tokens->value, "<", 2) == 0 || \
					ft_strncmp(tokens->value, "<<", 3) == 0)
				tokens->type = 'r';
			else if (ft_strncmp(tokens->value, "|", 2) == 0)
				tokens->type = 'c';
			else
			{
				ft_putstr_fd("Minishell: Syntax error: unexpected token '", 2);
				ft_putstr_fd(tokens->value, 2);
				ft_putstr_fd("'\n", 2);
				return (-1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}
