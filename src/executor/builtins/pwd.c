/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:03:55 by opelser           #+#    #+#             */
/*   Updated: 2023/11/15 16:01:58 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(int fd_out)
{
	char	cwd[1024];

	if (!getcwd(cwd, 1024))
	{
		print_error("getcwd", NULL, strerror(errno));
		return (1);
	}
	if (write(fd_out, cwd, ft_strlen(cwd)) == -1)
		return (1);
	if (write(fd_out, "\n", 1) == -1)
		return (1);
	return (0);
}
