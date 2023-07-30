/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   declarations.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 16:37:49 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/30 17:32:12 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECLARATIONS_H
# define DECLARATIONS_H

#include <stdbool.h>
#include <sys/types.h>

// ======== enums =========================================================== //

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

// ======== structs ========================================================= //

// this is what the lexer should return :
typedef struct	s_input t_input;

struct s_input
{
	char			*str;
	bool			spaces;
	t_token_type	token_type;

	t_input			*next;
};

typedef struct	s_redirect t_redirect;

struct s_redirect 
{
	t_token_type	type; // The token type i.e. output redirect
	int				fd; // The file descriptor
	char			*name; // The name of the file to redirect to or the delimiter for heredocs

	t_redirect		*next;
};

// this is what parse should return :
typedef struct	s_command t_command;

struct s_command
{
	char			**argv; // The argument vector for the current command

	t_redirect		*input; // A list of input redirects for the current command
	t_redirect		*output; // A list of output redirects for the current command

	pid_t			pid;

	t_command		*next;
};

typedef struct	s_environment_pointers t_envp;

struct s_environment_pointers
{
	char	*str; // The complete string

	char	*id; // The first part of the string, before the =
	char	*value; // The second part of the string, after the =

	t_envp	*prev;
	t_envp	*next;
};

typedef struct	s_program_data t_data;

struct s_program_data
{
	t_envp		*envp; // The environment environment list, formatted as a linked list
	t_command	*command; // The current command the program is working on
	int			exit_code; // The last received exit code of a program or function
};

// ======== ASCII =========================================================== //

#define ASCII "\
███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓     \n\
▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    \n\
▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    \n\
▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    \n\
▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒\n\
░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░\n\
░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░\n\
░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   \n\
       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░\n"

#endif
