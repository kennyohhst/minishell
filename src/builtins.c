/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 21:08:18 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/10 16:53:58 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_options(char *options)
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

int	echo(char **argv)
{
	char	newline;
	int		i;

	newline = '\n';
	i = 1;
	if (!argv[i])
	{
		write(1, "\n", 1);
		return (1);
	}
	if (check_options(argv[1]))
	{
		newline = '\0';
		i++;
	}
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	write(1, &newline, 1);
	return (1);
}
