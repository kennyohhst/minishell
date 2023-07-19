/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 15:51:53 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/19 14:50:52 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../lib/libft/include/libft.h"

/** @return A file descriptor to the created heredoc file or -1 on failure */
int		heredoc(char *delim)
{
	int		fd[2];
	char	*str;

	if (pipe(fd) == -1)
		return (-1);

	write(STDOUT_FILENO, "> ", 2);
	str = get_next_line(STDIN_FILENO);
	while (str && ft_strncmp(delim, str, ft_strlen(str) - 1))
	{
		write(fd[1], str, ft_strlen(str));
		free(str);
		write(STDOUT_FILENO, "> ", 2);
		str = get_next_line(STDIN_FILENO);
	}
	close (fd[1]);
	return (fd[0]);
}