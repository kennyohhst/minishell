/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 21:20:41 by opelser       #+#    #+#                 */
/*   Updated: 2023/09/14 15:18:17 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_data *data, char **argv)
{
	int		exit_code;
	int		argc;

	if (!argv[1])
		exit(data->exit_code);
	argc = 1;
	while (argv[argc])
		argc++;
	if (ft_err_atoi(argv[1], &exit_code) != 0)
	{
		print_error("exit", NULL, "numeric argument required");
		exit(2);
	}
	if (argc > 2)
	{
		print_error("exit", NULL, "too many arguments");
		return (1);
	}
	exit_code %= 256;
	if (exit_code < 0)
		exit_code += 256;
	exit(exit_code);
}
