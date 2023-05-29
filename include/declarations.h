/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   declarations.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 16:37:49 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/29 20:31:01 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECLARATIONS_H
# define DECLARATIONS_H

// ======== enums =========================================================== //

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

// ======== structs ========================================================= //

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

typedef struct	s_environment_pointers t_envp;

struct s_environment_pointers
{
	char	*str;
	char	*id;
	char	*value;
	int		equal;
	int		plus;
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

#endif
