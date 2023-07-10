/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fake_input_creation.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/12 00:29:30 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/10 20:29:52 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

char	**copy_2d_arr(char **arr)
{
	char	**new;
	int		size = 0;

	while (arr[size])
		size++;
	new = (char **) calloc((size + 1), sizeof(char *));
	for (int i = 0; i < size; i++)
		new[i] = strdup(arr[i]);
	return (new);
}

t_input		*new_input_node(t_token_type type)
{
	t_input		*input;

	input = (t_input *) calloc(1, sizeof(t_input));
	input->str = NULL;
	input->spaces = 0;
	input->token_type = type;
	input->next = NULL;
	return (input);
}

t_command	*new_cmd_node(char **argv)
{
	t_command	*cmd;

	cmd = (t_command *) calloc(1, sizeof(t_command));
	cmd->argv = copy_2d_arr(argv);
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_redirect	*new_redirect_node(char *name, t_token_type type)
{
	t_redirect *node;

	node = (t_redirect *) calloc(1, sizeof(t_redirect));
	node->name = name;
	node->type = type;
	node->next = NULL;
	return (node);
}

t_command	*init_cmds(void)
{
	t_command	*cmds;
	t_command	*head;
	char	*argv1[3] = {"/bin/cat", "test.c", NULL};
	char	*argv2[3] = {"/usr/bin/wc", "-l", NULL};
	char	*argv3[3] = {"/bin/cat", "-e", NULL};
	char	*argv4[3] = {"/bin/cat", "-e", NULL};
	char	*argv5[3] = {"/bin/cat", "-e", NULL};
	char	**argvs[6] = {argv1, argv2, argv3, argv4, argv5, NULL};

	cmds = new_cmd_node(argvs[0]);
	head = cmds;
	for (int i = 1; argvs[i]; i++)
	{
		cmds->next = new_cmd_node(argvs[i]);
		cmds = cmds->next;
	}
	head->redirects = new_redirect_node("output.txt", OUTPUT_REDIRECT);
	return (head);
}
