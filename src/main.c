/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 17:50:45 by kkalika       #+#    #+#                 */
/*   Updated: 2023/05/04 20:45:19 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_check(t_token *cmd)
{
	t_token	*temp;

	temp = cmd;
	while (temp)
	{
		printf("%s\t\t\t\t\t :\t%d\n", temp->str, temp->type);
		temp = temp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*cmd;
	char	*cmd_path;

	(void) argc;
	cmd = NULL;
	while (1)
	{
		parse(&cmd, (char *) 1);
		cmd_path = get_command_path(cmd->str);
		if (!execute(cmd_path, argv, envp))
		{
			free(cmd_path);
			ft_free_list(cmd);
			return (1);
		}
		list_check(cmd);
		if (cmd)
		{
			ft_free_list(cmd);
			cmd = NULL;
		}
	}
	return (0);
}
