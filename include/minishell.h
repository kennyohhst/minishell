/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 17:47:25 by kkalika       #+#    #+#                 */
/*   Updated: 2023/05/08 21:20:47 by opelser       ########   odam.nl         */
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
}		t_type;

typedef struct s_token t_token;

struct s_token
{
	char		*str;
	t_type		type;
	t_token		*next;	
};

//			make struct for exit codes and keeping track of process things?

// typedef	struct	pid
// {
// 	pid_t	pid;
// }t_p;

//		~ list_functions.c

void	create_list(t_token **cmd, char *str);
void	add_nodes(t_token **cmd, t_token *temp, char *str, int type);
void	ft_free_list(t_token *list);

//		~ parse.c

int		parse(t_token **cmd, char *raw_input);

//		~ quote_count.c

int		quote_count(char *str);

//		~ tokens.c

int		p_d_token(t_token **cmd, char *str, int i, char c);
int		e_var_token(t_token **cmd, char *str);
int		d_quotes_token(t_token **cmd, char *str);
int		s_quotes_token(t_token **cmd, char *str);		
int		std_token(t_token **cmd, char *str);

//		~ valid_pipe_check.c

int		valid_pipe_check(char *str);

//		~ get_command_path.c

char	*get_command_path(char *command);

//		~ execute.c

int		execute(t_token *cmd, char **envp);

//		~ builtins.c

int		echo(char **argv);


#endif