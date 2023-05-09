/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 21:08:18 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/08 21:18:57 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!ft_strncmp("-n", argv[1], 3))
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
	write(1, "\n", 1);
	return (1);
}