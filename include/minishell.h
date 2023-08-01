/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: code <code@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:47:25 by kkalika           #+#    #+#             */
/*   Updated: 2023/08/01 21:40:59 by code             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "../lib/libft/include/libft.h"
# include "declarations.h"
# include "colors.h"
# include "errno.h"

//		~ test (remove later)
void		test_data(t_data *data);
void		list_check(t_input *tokenized_input);

//		~ create_input_list.c

void		create_input_list(t_input **cmd, char *str);
void		add_nodes(t_input **cmd, t_input *temp, char *str, int type);
void		free_tokens(t_input *list);

//		~ lexer.c

void		create_input_list(t_input **cmd, char *str);
void		add_nodes(t_input **cmd, t_input *temp, char *str, int type);
void		free_tokens(t_input *list);
void		init_signals(void);

// ======== env utils ======================================================= //

t_envp		*environ_to_list(char **environ);
t_envp		*create_new_envp_node(char *str);
void		*free_envp_list(t_envp *node);
char		**envp_list_to_arr(t_envp *envp);
char		*ft_getenv(t_envp *envp_list, char *id);
t_envp		*add_envp_node_to_list(t_envp *list, t_envp *new);

// ======= lexer ============================================================ //

t_input		*lexer(void);
int			check_quotes(char *str);

int			p_d_token(t_input **cmd, char *str, int i, char c);
int			e_var_token(t_input **cmd, char *str);
int			d_quotes_token(t_input **cmd, char *str);
int			s_quotes_token(t_input **cmd, char *str);		
int			std_token(t_input **cmd, char *str);
t_input		*expander(t_input *token, t_data *data);

// ======== valid_pipe_check.c ============================================== //

int			valid_pipe_check(char *str);

// ======== parser ========================================================== //

int			valid_input_check(t_input *token, t_input *temp);
t_command	*parser(t_input *tokens);
int			list_length(t_input *input);

// ========= executer ======================================================= //

// set_command_path.c
int			set_command_path(t_command *cmd_struct, t_envp *envp_list);

// execute.c
void		close_fds(int fd_in, int fd_out);
int			execute(t_data *data);

// simulate_input.c
t_command	*init_cmds(void);

// heredoc.c
int			heredoc(char *delim);

// redirect.c
int			handle_redirects(t_command *cmd, int *fd_in, int *fd_out);

// ========= executer/builtins=============================================== //

bool		is_builtin(char **argv);
int			handle_builtin(t_command *cmd, t_data *data, int fd_in, int fd_out);

int			echo(char **argv, int fd_out);
int			pwd(int fd_out);
int			env(t_envp *envp, int fd_out);
int			cd(char **argv, t_envp *envp);
int			export(t_data *data, char **argv, int fd_out);
int			unset(t_data *data, char **argv);
int			ft_exit(t_data *data, char **argv);

// ========= free_data======================================================= //

void	free_cmd(t_command *cmd);
void	free_envp(t_envp *envp);

#endif
