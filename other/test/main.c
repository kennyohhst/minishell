/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:47:12 by opelser           #+#    #+#             */
/*   Updated: 2023/05/20 17:50:39 by kkalika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"

char	*parse(char **envp)
{
	int		i;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5))
		i++;
	return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
}

void	free_ptr_arr(void **ptrs)
{
	int		i;

	i = 0;
	while (ptrs[i])
	{
		free(ptrs[i]);
		i++;
	}
	free(ptrs);
}

char	*get_path(char **paths)
{
	int		i;

	i = 0;
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
			return (paths[i]);
		i++;
	}
	return (NULL);
}

// dont return NULL for malloc errors?
char	*get_command_location(char *command, char **paths)
{
	int		i;

	i = 0;
	command = ft_strjoin("/", command);
	if (!command)
		return (NULL);
	while (paths[i])
	{
		paths[i] = ft_strjoin_free(paths[i], command);
		if (!paths[i])
		{
			free_ptr_arr((void **) paths);
			return (NULL);
		}
		i++;
	}
	free(command);
	return (get_path(paths));
}

int	main(void)
{
	char	**split_paths;
	char	*paths;
	char	*command = "ls\0";
	char	*command_path;

	paths = getenv("PATH");
	// paths = parse(envp);
	if (!paths)
		return (1);

	split_paths = ft_split(paths, ':');
	if (!split_paths)
		return (2);

	command_path = get_command_location(command, split_paths);
	if (!command_path)
		return (free_ptr_arr((void **) split_paths), 3);

	command = malloc(ft_strlen(command) + 1);
	if (!command)
		return (free_ptr_arr((void **) split_paths), 4);
	ft_strlcpy(command, command_path, ft_strlen(command_path) + 1);
	free_ptr_arr((void **) split_paths);
	execve(command, NULL, NULL);
}
