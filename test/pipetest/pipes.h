/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/12 00:28:26 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/17 16:08:20 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "declarations.h"
# include "colors.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <string.h>

// simulate_input.c
t_command	*init_cmds(void);

// heredoc.c
int			heredoc(char *delim);

// redirect.c
void		create_output_files(t_command *cmd);
int			handle_redirects(t_command *cmd, int *fd_in, int *fd_out);

#endif