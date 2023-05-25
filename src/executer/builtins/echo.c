/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 21:08:18 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/25 21:35:21 by opelser       ########   odam.nl         */
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

void	echo(char **argv)
{
	char	newline;
	int		i;

	newline = '\n';
	i = 1;
	if (!argv[i])
	{
		write(1, "\n", 1);
		return ;
	}
	if (is_valid_option(argv[1]) == true)
	{
		newline = '\0';
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	printf("%c", newline);
	return ;
}
