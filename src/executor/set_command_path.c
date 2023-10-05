/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalika <kkalika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:43:02 by opelser           #+#    #+#             */
/*   Updated: 2023/10/05 19:32:29 by kkalika          ###   ########.fr       */
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
			return (NULL);
		i++;
	}
	tmp = access_paths(paths);
	if (tmp)
		tmp = ft_strdup(tmp);
	return (tmp);
}

int	set_command_path(t_command *cmd_struct, t_envp *envp_list)
{
	char	*paths;
	char	**split_paths;
	char	*command_path;

	if (ft_strchr(cmd_struct->argv[0], '/'))
		return (0);
	paths = ft_getenv(envp_list, "PATH");
	if (!cmd_struct->argv[0][0])
		return (1);
	if (!paths)
		return (2);
	split_paths = ft_split(paths, ':');
	if (!split_paths)
		return (3);
	command_path = get_command_location(cmd_struct->argv[0], split_paths);
	ft_free_str_arr(split_paths);
	if (!command_path)
		return (4);
	free(cmd_struct->argv[0]);
	cmd_struct->argv[0] = command_path;
	return (0);
}
