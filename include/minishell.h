/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 17:47:25 by kkalika       #+#    #+#                 */
/*   Updated: 2023/05/26 17:00:45 by opelser       ########   odam.nl         */
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

// ======= init ============================================================= //

void		create_input_list(t_input **cmd, char *str);
void		add_nodes(t_input **cmd, t_input *temp, char *str, int type);
void		ft_free_input_list(t_input *list);
void		init_signals(void);

// ======== env utils ======================================================= //

t_envp		*environ_to_list(char **environ);
t_envp		*create_new_envp_node(char *str);
void		print_envp_list(t_envp *envp);
int			ft_strchr_index(char *str, char c);
void		*free_envp_list(t_envp *node);
char		**envp_list_to_arr(t_envp *envp);

// ======= lexer ============================================================ //

t_input		*lexer(void);
int			check_quotes(char *str);

// ======= lexer/tokens ===================================================== //

int			p_d_token(t_input **cmd, char *str, int i, char c);
int			e_var_token(t_input **cmd, char *str);
int			d_quotes_token(t_input **cmd, char *str);
int			s_quotes_token(t_input **cmd, char *str);
int			std_token(t_input **cmd, char *str);
t_input 	*expander(t_input *token);

// ======== valid_pipe_check.c ============================================== //

int			valid_pipe_check(char *str);

// ======== parser ========================================================== //

t_command	*parser(t_input *tokens);
char		**get_command_argv(t_input *input);

// ========= executer ======================================================= //

int			execute(t_data *data);
char		*get_command_path(char *command);

// ======== executor/builtins =============================================== //

void		echo(char **argv);
int			pwd(void);
void		env(t_envp *envp);
int			cd(char **argv);
void		ft_export(t_data *data);
void		unset(t_data *data);

#endif
