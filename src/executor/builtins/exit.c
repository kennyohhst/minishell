/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 21:20:41 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/31 22:44:31 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_data *data, char **argv)
{
	int		exit_code;
	int		argc;

	dprintf(STDERR_FILENO, "exit\n");
	argc = 1;
	while (argv[argc])
		argc++;
	if (argc > 2)
	{
		dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return (1);
	}
	if (argv[1])
	{
		if (ft_err_atoi(argv[1], &exit_code) == 2)
		{
			dprintf(STDERR_FILENO, "minishell: exit: %s: numeric argument required\n", argv[1]);
			exit_code = 255;
		}
	}
	else
		exit_code = data->exit_code;
	exit_code %= 256;
	if (exit_code < 0)
		exit_code += 256;
	exit(exit_code);
}
