/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_argv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:43:09 by opelser           #+#    #+#             */
/*   Updated: 2023/05/20 17:53:03 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	list_length(t_input *input)
{
	int		count;

	if (!input)
		return (0);
	count = 0;
	while (input && input->token_type > 6)
	{
		input = input->next;
		count++;
	}
	return (count);
}

char	**get_command_argv(t_input *input)
{
	char		**argv;
	int			i;
	int			len;

	len = list_length(input);
	i = 0;
	if (!input)
		return (NULL);
	argv = malloc((len + 1) * sizeof(char *));
	if (!argv)
		return (NULL);
	while (input && input->token_type > 6)
	{
		argv[i] = ft_strdup(input->str);
		input = input->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
