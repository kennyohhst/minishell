/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:47:25 by kkalika           #+#    #+#             */
/*   Updated: 2023/05/20 17:47:13 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../lib/libft/include/libft.h"
#include <signal.h>
#include <sys/wait.h>

typedef struct	s_program_data t_program_data;

struct s_program_data
{
	char		**envp;
	int			exit_code;
};

typedef enum e_type
{
	PIPE_1,
	PIPE_2,
	O_RED_1,
	O_RED_2,
	I_RED_1,
	I_RED_2,
	E_VARIABLE,
	DQ_STRING,
	DQE_STRING,
	SQ_STRING,
	STRING
}		t_token_type;

// this is what the lexer should return :
typedef struct	s_input t_input;

struct s_input
{
	char			*str;
	t_token_type	token_type;
	t_input			*next;
};

// this is what the parser should make out of the lexer tokenized list :
typedef struct	s_redirect t_redirect;

struct s_redirect 
{
	char			*name; // this is the name of the files or the delimiter after the redirect, so like "cat > [outfile]"
	t_token_type	type;
	t_redirect		*next;
};

// this is what parse should return :
typedef struct	s_command t_command;

struct s_command
{
	char			**argv;
	t_redirect		*redirects;
	t_command		*next;
};

//		~ list_functions.c

void	create_list(t_input **cmd, char *str);
void	add_nodes(t_input **cmd, t_input *temp, char *str, int type);
void	ft_free_list(t_input *list);

//		~ lexer.c

t_input	*lexer(void);

//		~ quote_count.c

int		check_quotes(char *str);

//		~ tokens.c

int		p_d_token(t_input **cmd, char *str, int i, char c);
int		e_var_token(t_input **cmd, char *str);
int		d_quotes_token(t_input **cmd, char *str);
int		s_quotes_token(t_input **cmd, char *str);		
int		std_token(t_input **cmd, char *str);
t_input *expander(t_input *token);


//		~ valid_pipe_check.c

int		valid_pipe_check(char *str);

//		~ parser.c

t_command	*parser(t_input *tokens);

//		~ get_command_path.c

char	*get_command_path(char *command);

//		~ execute.c

int		execute(t_program_data *data, t_command **cmd);

//		~ signals.c

void	init_signals(void);

//		~ builtins

int		echo(char **argv);
void	pwd(char **argv);
void	env(char **argv, char **envp);
int		cd(char **argv);

//		~ get_command_argv.c

char	**get_command_argv(t_input *input);

#endif
