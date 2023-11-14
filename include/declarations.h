/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   declarations.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 16:37:49 by opelser       #+#    #+#                 */
/*   Updated: 2023/11/14 12:50:40 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECLARATIONS_H
# define DECLARATIONS_H

# include <stdbool.h>
# include <sys/types.h>

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

typedef enum e_signals
{
	MAIN,
	HEREDOC,
	IGNORE,
	CHILD
}	t_signals;

// ======== structs ========================================================= //

/**
 * @param *str The string belonging to the token
 * @param token_type An int describing the type of token
 */
typedef struct s_input					t_input;

struct s_input
{
	char			*str;
	int				argcount;
	t_token_type	token_type;
	\
	t_input			*next;
};

/**
 * @param type The token type i.e. output redirect
 * @param *name The name of the file to redirect to or the delimiter for heredocs
 * @param heredoc_fd The file descriptor for the temporary heredoc file
 */
typedef struct s_redirect				t_redirect;

struct s_redirect
{
	t_token_type	type;
	char			*name;
	int				heredoc_fd;
	\
	t_redirect		*next;
};

/**
 * @param **argv The argument vector for the current command
 * @param *input A list of input redirects for the current command
 * @param *output A list of output redirects for the current command
 * @param pid The process id of the forked process that's executing the command
 */
typedef struct s_command				t_command;

struct s_command
{
	char			**argv;
	\
	t_redirect		*redirects;
	\
	pid_t			pid;
	\
	t_command		*next;
};

/**
 * @param *str The complete string including the '=' sign
 * @param *id The identifier / first part of the string, before the =
 * @param *value The second part of the string, after the =
 */
typedef struct s_environment_pointers	t_envp;

struct s_environment_pointers
{
	char	*str;
	\
	char	*id;
	char	*value;
	\
	t_envp	*prev;
	t_envp	*next;
};

/**
 * @param *envp The environment list, formatted as a linked list
 * @param *command The current command the program is working on
 * @param exit_code The last received exit code of a program or function
 */
typedef struct s_data					t_data;

struct s_data
{
	t_envp		*envp;
	t_command	*command;
	int			exit_code;
};

// ======== ASCII =========================================================== //

# define ASCII "\
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
