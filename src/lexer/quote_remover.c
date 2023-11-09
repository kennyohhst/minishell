/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: code <code@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:19:02 by kkalika           #+#    #+#             */
/*   Updated: 2023/11/08 15:52:16 by code             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	repetitive_quotes(char *str, char c)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)		
			count++;
		i++;
	}
	if (count == i)
		ft_memset(str, '\0', ft_strlen(str));
}



void handle_quotes(char *str, char c, char d, bool quote)
{
    size_t		i;
	int		x;
    
	(void) quote;
	(void) d;
	x = 0;
    i = 0;
	repetitive_quotes(str, c);
	while (i < ft_strlen(str))
	{
		if (str[i] == c)
		{
			ft_memmove(str+i, str+(i+1), ft_strlen(str+i));
			// printf("\nstring =	%s\n  i =	%ld\n quote = %c\n", str, i, c);
			x++;
			continue ;
		}
		else if (str[i] == d && (x % 2) == 0 && quote == false)
		{
			handle_quotes(str+i, d, c, false);
			// printf("string quote : 	%s\n", str);
			return ;
			// quote = true;
			// i--;
			// x = -2;
		// 	// return ;
		}
		i++;
	}
}

void    type_read(t_input *tokens)
{
    t_input *temp;

    temp = tokens;
    while (temp)
    {
        if (temp->token_type == DQ_STRING)
            handle_quotes(temp->str, '\"', '\'', false);
        if (temp->token_type == SQ_STRING)
            handle_quotes(temp->str, '\'', '\"', false);
        temp = temp->next;
    }
}