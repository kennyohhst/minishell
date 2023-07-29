/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 21:08:18 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/30 01:23:10 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_option(char *options)
{
	int		i;

	i = 1;
	if (options[0] != '-')
		return (0);
	while (options[i])
	{
		if (options[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int print_strings(char **argv, int fd_out, int i)
{
	while (argv[i])
	{
		if (dprintf(fd_out, "%s", argv[i]) == -1)
			return (-1);
		if (argv[i + 1] && dprintf(fd_out, " ") == -1)
			return (-1);
		i++;
	}
	return (1);
}

int	echo(char **argv, int fd_out)
{
	char	newline;
	int		start;

	newline = '\n';
	start = 1;
	if (!argv[1])
	{
		if (dprintf(fd_out, "\n") == -1)
			return (1);
		return (0);
	}
	if (is_valid_option(argv[1]) == true)
	{
		newline = '\0';
		start++;
	}
	if (print_strings(argv, fd_out, start) == -1)
		return (1);
	dprintf(fd_out, "%c", newline);
	return (0);
}
