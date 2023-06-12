/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/12 00:28:26 by opelser       #+#    #+#                 */
/*   Updated: 2023/06/12 16:32:09 by opelser       ########   odam.nl         */
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

char		**copy_2d_arr(char **arr);
t_input		*new_input_node(t_token_type type);
t_command	*new_cmd_node(char **argv);
t_command	*init_cmds(void);

#endif