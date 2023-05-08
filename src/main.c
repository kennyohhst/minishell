/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkalika <kkalika@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 17:50:45 by kkalika       #+#    #+#                 */
/*   Updated: 2023/05/08 16:33:53 by opelser       ########   odam.nl         */
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

void	handle_sig(int sig)
{
	write(1, "\n", 1);
	if (sig == 2)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int		list_length(t_token *node)
{
	int		count;

	count = 0;
	if (!node)
		return (0);
	while (node)
	{
		node = node->next;
		count++;
	}
	return (count);
}

char	**get_command_argv(t_token *node, const int len)
{
	char		**argv;
	int			i;

	i = 0;
	if (!node)
		return (NULL);

	argv = malloc((len + 1) * sizeof(char *));
	if (!argv)
		return (NULL);

	while (node)
	{
		argv[i] = ft_strdup(node->str);
		node = node->next;
		i++;
	}

	argv[i] = NULL;

	return (argv);
}

extern int rl_catch_signals;

int	main(int argc, char **argv, char **envp)
{
	t_token		*cmd;
	char		*cmd_path;
	char		**cmd_argv;

	(void) argc;
	(void) argv;
	cmd = NULL;
	signal(SIGINT, handle_sig);
	rl_catch_signals = 0;
	while (1)
	{
		if (parse(&cmd, (char *) 1) == -1)
			return (1);
		if (!cmd)
			continue ;
		cmd_argv = get_command_argv(cmd, list_length(cmd));
		if (!cmd_argv)
			return (2);
		cmd_path = get_command_path(cmd_argv[0]);
		if (!execute(cmd_path, cmd_argv, envp))
		{
			free(cmd_path);
			ft_free_list(cmd);
			return (3);
		}
		// list_check(cmd);
		if (cmd)
		{
			ft_free_list(cmd);
			cmd = NULL;
		}
	}
	return (0);
}
