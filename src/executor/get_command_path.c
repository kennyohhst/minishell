/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_command_path.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 20:43:02 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/27 15:29:28 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*access_paths(char **paths)
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
	if (!tmp)
		return (NULL);
	command = tmp;
	while (paths[i])
	{
		paths[i] = ft_strjoin_free(paths[i], command);
		if (!paths[i])
		{
			free(command);
			ft_free_str_arr(paths);
			return (NULL);
		}
		i++;
	}
	free(command);
	return (access_paths(paths));
}

char	*get_command_path(char *command, t_envp *envp_list)
{
	char	**split_paths;
	char	*paths;
	char	*command_path;

	if (!ft_strncmp("../", command, 3) || !ft_strncmp("./", command, 2))
		return (ft_strdup(command));
	paths = ft_getenv(envp_list, "PATH");	// get envp from envp list
	if (!paths)
		return (NULL);
	split_paths = ft_split(paths, ':');
	if (!split_paths)
		return (NULL);
	command_path = get_command_location(command, split_paths);
	if (!command_path)
		return (ft_free_str_arr(split_paths), NULL);
	command = ft_strdup(command_path);
	ft_free_str_arr(split_paths);
	return (command);
}
