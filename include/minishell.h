/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 17:47:25 by kkalika       #+#    #+#                 */
/*   Updated: 2023/08/02 16:56:37 by opelser       ########   odam.nl         */
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

void		create_input_list(t_input **cmd, char *str);
void		add_nodes(t_input **cmd, t_input *temp, char *str, int type);
void		free_tokens(t_input *list);

//		~ lexer.c

void		create_input_list(t_input **cmd, char *str);
void		add_nodes(t_input **cmd, t_input *temp, char *str, int type);
void		free_tokens(t_input *list);
void		init_signals(void);

// ======== env utils ======================================================= //

void		lst_add_back_envp(t_envp *node, t_envp *new_node);
t_envp		*environ_to_list(char **environ);
t_envp		*create_new_envp_node(char *str);
void		*free_envp_list(t_envp *node);
char		**envp_list_to_arr(t_envp *envp);
char		*ft_getenv(t_envp *envp_list, char *id);

// ======= lexer ============================================================ //

t_input		*lexer(char *input);
int			check_quotes(char *str);

int			p_d_token(t_input **cmd, char *str, int i, char c);
int			e_var_token(t_input **cmd, char *str);
int			d_quotes_token(t_input **cmd, char *str);
int			s_quotes_token(t_input **cmd, char *str);
int			std_token(t_input **cmd, char *str);
t_input		*expander(t_data *data, t_input *token);

// ======== valid_pipe_check.c ============================================== //

int			valid_pipe_check(char *str);

// ======== parser ========================================================== //

int			valid_input_check(t_input *token);
t_command	*parser(t_input *tokens);
int			list_length(t_input *input);

// ========= executer ======================================================= //

int			set_command_path(t_command *cmd_struct, t_envp *envp_list);
int			execute(t_data *data);
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
