/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/20 18:31:06 by opelser       #+#    #+#                 */
/*   Updated: 2023/01/08 17:06:16 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE > 6000000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 420
# endif

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_read(int fd, char *buf);
void	ft_copy(char *dst, char const *src, size_t offset, size_t len);
char	*ft_strjoin_free(char *s1, char const *s2);

#endif
