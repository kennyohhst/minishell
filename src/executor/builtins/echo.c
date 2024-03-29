/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 21:08:18 by opelser       #+#    #+#                 */
/*   Updated: 2023/09/14 15:04:09 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_option(char *options)
{
	int		i;

	i = 1;
	if (options[0] != '-')
		return (false);
	while (options[i])
	{
		if (options[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static int	print_strings(char **argv, int fd_out)
{
	bool	newline;
	int		i;

	newline = true;
	i = 1;
	while (argv[i] && is_valid_option(argv[i]) == true)
	{
		newline = false;
		i++;
	}
	while (argv[i])
	{
		if (write(fd_out, argv[i], ft_strlen(argv[i])) == -1)
			return (-1);
		if (argv[i + 1] && write(fd_out, " ", 1) == -1)
			return (-1);
		i++;
	}
	if (newline)
		write(fd_out, "\n", 1);
	return (1);
}

int	echo(char **argv, int fd_out)
{
	if (!argv[1])
	{
		if (write(fd_out, "\n", 1) == -1)
			return (1);
		return (0);
	}
	if (print_strings(argv, fd_out) == -1)
		return (1);
	return (0);
}
