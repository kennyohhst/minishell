/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:47:25 by kkalika           #+#    #+#             */
/*   Updated: 2023/04/28 16:46:56 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../lib/libft/include/libft.h"

typedef enum types
{
	PIPE_1,
	PIPE_2,
	O_RED_1,
	O_RED_2,
	I_RED_1,
	I_RED_2,
	E_VARIABLE,
	DQ_STRING,
	SQ_STRING,
	STRING
}t_type;

typedef struct tokens
{
	char			*str;
	t_type			type;
	struct tokens	*next;	
}t_token;

void	create_list(t_token **cmd, char *str);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_free_string_array(char **string);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	add_nodes(t_token **cmd, t_token *temp, char *str, int type);
void	ft_free_list(t_token *list);
void	parse(t_token **cmd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
int		quote_count(char *str);
int		p_d_token(t_token **cmd, char *str, int i, char c);
int		e_var_token(t_token **cmd, char *str);
int		d_quotes_token(t_token **cmd, char *str);
int		s_quotes_token(t_token **cmd, char *str);		
int		std_token(t_token **cmd, char *str);
int		valid_pipe_check(char *str);

#endif