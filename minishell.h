/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:47:25 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/14 18:33:26 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef struct tokens
{
	char			*str;
	struct tokens	*next;
	
}t_token;

void	create_list(t_token **cmd, char *str);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_free_s(char **string);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	ft_add_nodes(t_token **cmd, t_token *temp, char *str);
void	ft_free_list(t_token *list);
void	parse(t_token **cmd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strchr(char *s, int c);




#endif