/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 14:27:00 by opelser       #+#    #+#                 */
/*   Updated: 2023/09/14 15:20:41 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *program_name, char *arg, char *error_msg)
{
	write(STDERR_FILENO, "minishell: ", 11);
	if (program_name)
	{
		write(STDERR_FILENO, program_name, ft_strlen(program_name));
		write(STDERR_FILENO, ": ", 2);
	}
	if (arg)
	{
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	write(STDERR_FILENO, "\n", 1);
}
