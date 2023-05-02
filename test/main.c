/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 16:47:12 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/02 23:12:55 by opelser       ########   odam.nl         */
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
	return (get_path(paths));
}

int	main(int argc, char **argv, char **envp)
{
	char	**split_paths;
	char	*paths;
	char	*command;

	(void) argc;
	command = argv[1];

	paths = parse(envp);
	if (!paths)
		return (1);

	split_paths = ft_split(paths, ':');
	if (!split_paths)
		return (2);

	command = get_command_location(argv[1], split_paths);
	if (!command)
		return (3);

	execve(command, NULL, envp);
}
