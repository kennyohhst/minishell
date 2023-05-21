/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:08:18 by opelser           #+#    #+#             */
/*   Updated: 2023/05/21 17:50:55 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_options(char *options)
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
		exit (0);
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
	ft_free_str_arr(argv);
	exit (0);
}
