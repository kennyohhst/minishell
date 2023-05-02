/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 16:47:12 by opelser       #+#    #+#                 */
/*   Updated: 2023/05/02 21:36:07 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"

int		main(int argc, char **argv, char **envp)
{
	char	**split;
	char	*path;
	char	*command;
	char	*correct_path;
	
	(void) argc;
	command = argv[1];

	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	// printf("%s\n\n", *envp);

	path = ft_split(*envp, '=')[1];
	if (!path)
		return (1);
	// printf("%s\n\n", path);

	split = ft_split(path, ':');
	if (!split)
		return (1);
	// for (int i = 0; split[i]; i++)
	// 	printf("%s\n", split[i]);
	// putchar('\n');

	command = ft_strjoin("/", command);
	
	for (int i = 0; split[i]; i++)
		split[i] = ft_strjoin_free(split[i], command);
	// for (int i = 0; split[i]; i++)
	// 	printf("%s\n", split[i]);
	// putchar('\n');

	for (int i = 0; split[i]; i++)
	{
		if (access(split[i], F_OK) == 0)
			correct_path = split[i];
	}
	// printf("%s\n", correct_path);

	execv(correct_path, argv + 1);
}