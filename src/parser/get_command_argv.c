/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_argv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:43:09 by opelser           #+#    #+#             */
/*   Updated: 2023/05/26 17:38:42 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirects(t_command **command, t_input *input)
{
	if (!input)
		return ;
	while (input)
	{
		if (input->token_type == PIPE_1)
			(*command)->redirects->type = PIPE_1;
		if (input->token_type == PIPE_2)
			(*command)->redirects->type = PIPE_2;
		if (input->token_type == I_RED_1)
			(*command)->redirects->type = I_RED_1;
		if (input->token_type == O_RED_2)
			(*command)->redirects->type = O_RED_2;
	}
}

int	list_length(t_input *input)
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

char	**get_command_argv(t_input *input, t_command **command)
{
	char		**argv;
	int			i;
	
	i = 0;
	if (!input)
		return (NULL);
	argv = malloc((list_length(input) + 1) * sizeof(char *));
	if (!argv)
		return (NULL);
	while (input)
	{
		if (input->token_type > 6)
		{
			argv[i] = ft_strdup(input->str);
			input = input->next;
			i++;
		}
		else
		{
			argv[i] = NULL;
			redirects(command, input);
		}
	}
	argv[i] = NULL;
	return (argv);
}
