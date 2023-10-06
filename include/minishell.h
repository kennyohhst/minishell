/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:47:25 by kkalika           #+#    #+#             */
/*   Updated: 2023/10/06 18:44:41 by kkalika          ###   ########.fr       */
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

//		~ create_input_list.c

void		create_input_list(t_input **cmd, char *str, t_data data);
void		add_nodes(t_input **cmd, t_input *temp, char *str, int type);
t_input		*free_tokens(t_input *list);

//		~ lexer.c

// void		create_input_list(t_input **cmd, char *str);
// void		add_nodes(t_input **cmd, t_input *temp, char *str, int type);
void		init_signals(int s);

// ======== env utils ======================================================= //

void		lst_add_back_envp(t_envp *node, t_envp *new_node);
t_envp		*environ_to_list(char **environ);
t_envp		*create_new_envp_node(char *str);
void		*free_envp_list(t_envp *node);
char		**envp_list_to_arr(t_envp *envp);
char		*ft_getenv(t_envp *envp_list, char *id);

// ======= lexer ============================================================ //

t_input		*lexer(char *input, t_data data);
int			check_quotes(char *str);
int			quotes_finder(char *str, char c);
int			remove_quotes(char *str, char c);
int			std_remove_quotes(char *str, char c);
int			p_d_token(t_input **cmd, char *str, int i, char c);
int			e_var_token(t_input **cmd, char *str);
int			d_quotes_token(t_input **cmd, char *str, t_data data);
int			s_quotes_token(t_input **cmd, char *str);
int			std_token(t_input **cmd, char *str);
bool		expander(t_data data, char **token, char *temp, int i);

// ======== valid_pipe_check.c ============================================== //

int			valid_pipe_check(char *str);

// ======== parser ========================================================== //

int			valid_input_check(t_input *token);
bool		expand_edgecases(char c);
int			end_position(char *str);
int			skip_singles(int i, char *token);
int			find_start_exit_var(char *str);
t_command	*parser(t_input *tokens);
int			list_length(t_input *input);
void		test_data(t_data *data);
void		list_check(t_input *tokenized_input);
int			malloc_argv(t_input **token);
void		malloc_cmd_node(t_command **cmd, t_command *temp, t_input **token);
void		malloc_redirects_node(t_redirect **red, int type);
int			first_time(t_command **command, t_input **token, int i);
int			pipe_encounter(t_command **command, t_input **token, int i);

// ========= executer ======================================================= //

int			set_command_path(t_command *cmd_struct, t_envp *envp_list);
int			execute(t_data *data);
int			handle_redirects(t_command *cmd, int *fd_in, int *fd_out);
void		set_fds(int *fd_in, int *fd_out);
void		close_fds(int fd_in, int fd_out);
void		execve_error(char *arg);

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

void		free_cmd(t_command *cmd);
void		free_envp(t_envp *envp);

// ========= utils ========================================================== //

void		print_error(char *program_name, char *arg, char *error_msg);

#endif
