/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:09:42 by opelser           #+#    #+#             */
/*   Updated: 2023/11/15 16:46:59 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_oldpwd(t_data *data)
{
	char		*full_str;
	char		cwd[1024];
	t_envp		*new;

	if (!getcwd(cwd, 1024))
	{
		print_error("getcwd", NULL, strerror(errno));
		return (1);
	}
	full_str = ft_strjoin("OLDPWD=", cwd);
	if (!full_str)
	{
		print_error("cd", NULL, "strjoin failed");
		return (3);
	}
	new = create_new_envp_node(full_str);
	free(full_str);
	if (!new)
		return (3);
	add_envp_node(data, new);
	return (0);
}

static int	update_pwd(t_data *data)
{
	char		*full_str;
	char		cwd[1024];
	t_envp		*new;

	if (!getcwd(cwd, 1024))
	{
		print_error("getcwd", NULL, strerror(errno));
		return (1);
	}
	full_str = ft_strjoin("PWD=", cwd);
	if (!full_str)
	{
		print_error("cd", NULL, "strjoin failed");
		return (2);
	}
	new = create_new_envp_node(full_str);
	free(full_str);
	if (!new)
		return (3);
	add_envp_node(data, new);
	return (0);
}

static int	cd_oldpwd(t_data *data)
{
	char	*old_pwd;

	old_pwd = ft_getenv(data->envp, "OLDPWD");
	if (!old_pwd)
	{
		print_error("cd", NULL, "OLDPWD not set");
		return (1);
	}
	if (chdir(old_pwd) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	update_pwd(data);
	return (0);
}

static int	cd_home(t_data *data)
{
	char	*home;

	home = ft_getenv(data->envp, "HOME");
	if (!home)
	{
		print_error("cd", NULL, "HOME not set");
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	update_pwd(data);
	return (0);
}

int	cd(t_data *data, char **argv)
{
	if (argv[1] && argv[2])
	{
		print_error("cd", NULL, "too many arguments");
		return (1);
	}
	update_oldpwd(data);
	if (!argv[1])
		return (cd_home(data));
	if (ft_strcmp(argv[1], "~") == 0)
		return (cd_home(data));
	if (ft_strcmp(argv[1], "-") == 0)
		return (cd_oldpwd(data));
	if (chdir(argv[1]) == -1)
	{
		print_error("cd", argv[1], strerror(errno));
		return (1);
	}
	update_pwd(data);
	return (0);
}
