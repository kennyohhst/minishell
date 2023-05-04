# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

// void	handle_q(int sig)
// {
// 	if (sig == 3)
// 	{
// 		printf("you did it again\n");
// 		exit(1);
// 	}
// }

void	handle_sig(int sig)
{
	printf("sig == %d\n", sig);
	if (sig == 2)
	{
		printf("you did it\n");
	}
	if (sig == 3)
	{
		printf("you did it again\n");
		exit(1);
	}
}

int main(void)
{
	while(1)
	{
		// signal(SIGQUIT, handle_q);
		signal(SIGINT, handle_sig);
		char *i = readline("bla: ");
		if (!i)
			exit(write(2, " \nexit\n", 7));

	}
	return (0);
}