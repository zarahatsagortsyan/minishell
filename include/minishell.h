/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:53:26 by salaverd          #+#    #+#             */
/*   Updated: 2022/07/11 20:24:44 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	char			meaning;
	int				status;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			type;
	char			*value;
	char			*quote;
	struct s_token	*next;
}					t_token;

typedef struct s_command
{
	int					id;
	char				**args;
	char				*path;
	int					path_error;
	char				*oper;
	char				*oper_value;
	char				delimitor;
	int					builtin;
	int					std_in;
	int					std_in_dup1;
	int					std_out;
	int					std_out_dup1;
	int					std_err;
	int					pipe;
	int					pipe_out;
	int					pipe_in;
	struct s_command	*next;
}						t_command;

int		env_list(char **envp, t_env **env_lst);
t_env	*lst_new_elem(char *name, char *value);
t_env	*lst_new_elem(char *name, char *value);
void	lst_add_back(t_env **lst, t_env *new_node);
void	lst_add_back_token(t_token **lst, t_token *new_node);
void	lst_add_front(t_env **lst, t_env *new_elem);
void	lst_clear_token(t_token **lst, void (*del)(void *));
void	lst_clear(t_env **lst, void (*del)(void *));
void	lst_delone(t_env *lst, void (*del)(void *));
void	lst_delone_token(t_token *lst, void (*del)(void *));
t_env	*lst_last(t_env *lst);
t_token	*lst_last_token(t_token *lst);
t_env	*lst_new_elem(char *name, char *value);
t_token	*lst_new_elem_token(char type, char *value);
void	shlvl(t_env **env_lst);
int		parsing(char *line, t_token **tokens, t_env **env_lst);
int		parsing_command(t_token **tokens, t_command *command, t_env **env_lst);
void	p_expansion(t_token *tokens, t_env *env_lst);
int		heredoc(t_command *command, t_env **env_lst);
void	command_free(t_command *command);
int		parsing_operators(t_token **tokens, t_command *command,
			t_env **env_lst);
int		tokens_count(char *line, char *metachars);
void	tokens_array(char *line, char *metachars, t_token **tokens);
void	tokens_trim(t_token **tokens);
int		tokens_to_struct(t_token **tokens, t_command **command,
			t_env **env_lst);
int		operators(t_token *tokens);
void	word_splitting(t_token **tokens, t_env *env_lst);
void	quote_removal(t_token *tokens);
int		arg_count(t_token **tokens, t_command *command);
void	change_status(t_env **env_lst, int status);
void	exec(t_command **command, t_env **env_lst);
void	signals_init(void);
void	child(t_command **command, t_env **env_lst, int id);
void	dups(t_command *tmp);
char	*strjoin_base(char const *s1, char const *s2, char c);
char	**env_lst_to_arr(t_env *env_lst, char meaning, int quote);
void	handle_sigint_heredoc(int sig);
void	arr_free(char **arr);
char	*find_command(t_command *command, t_env *env_lst);
void	exec_builtin(t_command *command, t_env **env_lst, int child_parent);
int		check_var_name(char *str, int *res, t_env **env_lst);
int		pwd(t_env **env_lst);
int		env(t_env **env_lst);
int		unset(t_command *command, t_env **env_lst);
int		export_env(t_command *command, t_env **env_lst);
int		echo(t_command *command, t_env **env_lst);
int		my_exit(t_command *command, t_env **env_lst);
int		cd(t_command *command, t_env **env_lst);
int		change_dir(char *path, t_env **env_lst);

#endif
