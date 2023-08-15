/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:26:49 by kkalika           #+#    #+#             */
/*   Updated: 2023/08/15 17:40:11 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	*lexer(char *input, t_data data)
{
	t_input		*input_list;
	// (void) data;

	ft_bzero(&input_list, sizeof(t_input *));
	if (input[0] != '\0')
		add_history(input);
	if (check_quotes(input))
		create_input_list(&input_list, input, data);
	return (input_list);
}
