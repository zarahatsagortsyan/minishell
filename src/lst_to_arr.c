/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:42:07 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/02 18:42:10 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_size(t_env *lst, char meaning)
{
	int	count;

	count = 0;
	while (lst != 0)
	{
		if ((meaning == 'x' && (lst->meaning == 'e' || lst->meaning == 'x' || \
						lst->meaning == 'q')) || \
				(meaning == 'e' && lst->meaning == 'e'))
			count++;
		lst = lst->next;
	}
	return (count);
}

static void	empties(t_env *env_lst, int *i, char **arr)
{
	char	*tmp_str1;
	char	*tmp_str2;

	if (env_lst->meaning == 'e')
	{
		tmp_str1 = ft_strdup(env_lst->name);
		tmp_str2 = ft_strdup("=\"\"");
		arr[*i] = ft_strjoin(tmp_str1, tmp_str2);
		free(tmp_str1);
		free(tmp_str2);
	}
	else
		arr[*i] = ft_strdup(env_lst->name);
}

static void	find_and_join(t_env *env_lst, int quote, char **arr, int *i)
{
	char	*tmp;

	if (quote == 1)
	{
		if (ft_strncmp(env_lst->value, "", ft_strlen(env_lst->value)) != 0 || \
				env_lst->meaning == 'q')
		{
			tmp = ft_strjoin(env_lst->name, "=\"");
			arr[*i] = ft_strjoin(tmp, env_lst->value);
			free(tmp);
			tmp = arr[*i];
			arr[*i] = ft_strjoin(tmp, "\"");
			free(tmp);
		}
		else
			empties(env_lst, i, arr);
		*i = *i + 1;
	}
	else
	{
		arr[*i] = strjoin_base(env_lst->name, env_lst->value, '=');
		*i = *i + 1;
	}
}

char	**env_lst_to_arr(t_env *env_lst, char meaning, int quote)
{
	int		size;
	int		i;
	char	**arr;

	i = 0;
	size = my_size(env_lst, meaning);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (arr == 0)
		return (0);
	arr[size] = 0;
	while (env_lst != 0)
	{
		if ((meaning == 'x' && (env_lst->meaning == 'e' || \
					env_lst->meaning == 'x' || env_lst->meaning == 'q')) || \
				(meaning == 'e' && env_lst->meaning == 'e'))
			find_and_join(env_lst, quote, arr, &i);
		env_lst = env_lst->next;
	}
	return (arr);
}
