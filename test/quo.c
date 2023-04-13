/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:21:14 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/13 18:23:30 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int test(char *str, int i)
{
	if (!str)
		return (0);
	while (str[i] && str[i] != 34 && str[i] != 39)
	{
		i++;
	}
	return (i);
}

int main(void)
{
	int i = 0;
	char str[] = "ike '1234' dont you think?";
	
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			printf("num:	%d\n", test(str, i));
		
		printf("what is this	:%c\n", str[i]);
		i++;
	}
	
	return (0);
}