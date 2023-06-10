/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:47:25 by kkalika           #+#    #+#             */
/*   Updated: 2023/06/10 16:57:33 by kkalika          ###   ########.fr       */
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
# include <signal.h>
# include <sys/wait.h>
# include <stdbool.h>

typedef enum e_type
{
	PIPE,
	OR,
	OUTPUT_REDIRECT,
	APPEND,
	INPUT_REDIRECT,
	HERE_DOC,
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
	bool			spaces;
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

typedef struct	s_environment_pointers t_envp;

struct s_environment_pointers
{
	char	*str;
	char	*id;
	char	*value;
	int		equal_index;
	t_envp	*prev;
	t_envp	*next;
};

typedef struct	s_program_data t_data;

struct s_program_data
{
	t_envp		*envp;
	t_command	*command;
	int			exit_code;
};

//		~ create_input_list.c

void	create_input_list(t_input **cmd, char *str);
void	add_nodes(t_input **cmd, t_input *temp, char *str, int type);
void	ft_free_input_list(t_input *list);

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
t_input *expander(t_input *token, t_data *data);


//		~ valid_pipe_check.c

int		valid_pipe_check(char *str);

//		~ parser.c

t_command	*parser(t_input *tokens);
int			list_length(t_input *input);


//		~ get_command_path.c

char	*get_command_path(char *command);

//		~ execute.c

int		execute(t_data *data);

//		~ signals.c

void	init_signals(void);

//		~ get_command_argv.c

char	**get_command_argv(t_input *input, t_command **command);

//		~ builtins

int		echo(char **argv);
int		pwd(char **argv);
void	env(t_envp *envp);
int		cd(char **argv);
void	ft_export(t_data *data);
void	unset(t_data *data);

//		~ environment

t_envp	*environ_to_list(char **environ);
t_envp	*create_new_envp_node(char *str);
char	*get_env_value(char *str, int equal_index);
void	print_envp_list(t_envp *envp);
int		ft_strchr_index(char *str, char c);
void	*free_envp_list(t_envp *node);
char	**envp_list_to_arr(t_envp *envp);

#endif
