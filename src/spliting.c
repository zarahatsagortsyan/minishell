/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:47:04 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:47:10 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	split_ifs(t_token *tmp, char *ifs, int *i)
{
	char	*new_str;
	t_token	*new_elem;
	int		j;

	j = *i;
	tmp->value[*i] = '\0';
	tmp->quote[*i] = '\0';
	while (ft_strchr(ifs, tmp->value[++j]) != 0 && tmp->value[j] != '\0')
		;
	new_elem = lst_new_elem_token('w', ft_strdup(&(tmp->value[j])));
	new_elem->quote = ft_strdup(&(tmp->quote[j]));
	new_elem->next = tmp->next;
	tmp->next = new_elem;
	new_str = ft_strdup(tmp->value);
	free(tmp->value);
	tmp->value = new_str;
	new_str = ft_strdup(tmp->quote);
	free(tmp->quote);
	tmp->quote = new_str;
	return (1);
}

static void	search_ifs(t_token **tokens, char *ifs)
{
	t_token	*tmp;
	int		i;

	tmp = *tokens;
	while (tmp != 0 && tmp->type != 'c')
	{
		i = -1;
		if (tmp->type != 'r' && tmp->type != 'h')
		{
			while (tmp->value[++i] != '\0')
			{
				if (tmp->value[i] == '\'' && tmp->quote[i] == '1')
					while (!(tmp->value[++i] == '\'' && tmp->quote[i] == '1'))
						;
				else if (tmp->value[i] == '\"' && tmp->quote[i] == '1')
					while (!(tmp->value[++i] == '\"' && tmp->quote[i] == '1'))
						;
				else if (ft_strchr(ifs, tmp->value[i]) != 0 && \
						tmp->quote[i] == '2' && split_ifs(tmp, ifs, &i))
					break ;
			}
		}
		tmp = tmp->next;
	}
}

void	word_splitting(t_token **tokens, t_env *env_lst)
{
	while (env_lst != 0)
	{
		if (ft_strncmp(env_lst->name, "IFS", 4) == 0)
			break ;
		env_lst = env_lst->next;
	}
	if (env_lst != 0)
		search_ifs(tokens, env_lst->value);
}
