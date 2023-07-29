/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 21:08:18 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/30 00:19:43 by opelser       ########   odam.nl         */
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

int	echo(char **argv)
{
	char	newline;
	int		i;

	newline = '\n';
	i = 1;
	if (!argv[i])
	{
		if (printf("\n") == -1)
			return (-1);
		return (0);
	}
	if (is_valid_option(argv[1]) == true)
	{
		newline = '\0';
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1] && printf(" ") == -1)
			return (-1);
		i++;
	}
	printf("%c", newline);
	return (0);
}
