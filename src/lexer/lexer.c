/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: code <code@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 17:26:49 by kkalika       #+#    #+#                 */
/*   Updated: 2023/08/10 13:45:14 by kkalika       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	*lexer(char *input, t_data data)
{
	t_input		*input_list;
	// (void) data;

	ft_bzero(&input_list, sizeof(t_input *));
	// input_list = NULL;
	if (input[0] != '\0')
		add_history(input);
	if (check_quotes(input))
		create_input_list(&input_list, input);
	expander(data, input_list);
	free(input);
	return (input_list);
}
