/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_command_path.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 20:43:02 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/08 20:27:47 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char **paths)
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

static char	*get_command_location(char *command, char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin("/", command);
	free(command);
	if (!tmp)
		return (NULL);
	command = tmp;
	while (paths[i])
	{
		paths[i] = ft_strjoin_free(paths[i], command);
		if (!paths[i])
		{
			ft_free_str_arr(paths);
			return (NULL);
		}
		i++;
	}
	return (get_path(paths));
}

char	*get_command_path(char *command)
{
	char	**split_paths;
	char	*paths;
	char	*command_path;

	paths = getenv("PATH");
	if (!paths)
		return (NULL);

	split_paths = ft_split(paths, ':');
	if (!split_paths)
		return (NULL);

	command_path = get_command_location(command, split_paths);
	if (!command_path)
		return (ft_free_str_arr(split_paths), NULL);

	command = malloc(ft_strlen(command_path) + 1);
	if (!command)
		return (ft_free_str_arr(split_paths), NULL);

	ft_strlcpy(command, command_path, ft_strlen(command_path) + 1);
	ft_free_str_arr(split_paths);
	return (command);
}
