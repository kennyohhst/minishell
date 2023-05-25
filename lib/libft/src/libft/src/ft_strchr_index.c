/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr_index.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 21:35:58 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/24 21:36:05 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_strchr_index(char *str, char c)
{
	int		i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}
