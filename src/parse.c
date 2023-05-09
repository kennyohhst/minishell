/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 17:26:49 by kkalika       #+#    #+#                 */
/*   Updated: 2023/05/09 21:42:19 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	raw_input_check(char *raw_input)
{
	if (!raw_input)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if (!ft_strncmp(raw_input, "exit", 5))
	{
		free(raw_input);
		exit(0);
	}
}

int	parse(t_token **cmd, char *raw_input)
{
	raw_input = readline("\e[1;33mC Shell >>\033[0m ");
	raw_input_check(raw_input);
	if (raw_input[0] == '\0')
	{
		free(raw_input);
		return (1);
	}
	add_history(raw_input);
	if ((check_quotes(raw_input) % 2) == 1)			// only checks for the first quote symbol you find, so ["string" 'string2] should be wrong but passes your check
		create_list(cmd, raw_input);
	free(raw_input);
	return (1);
}
