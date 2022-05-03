#include "../minishell.h"

void	very_important_function(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**args;

	very_important_function(argc, argv, envp);
	while (1)
	{
		input = readline("ඞabobusඞ> ");
		add_history(input);
		args = parser(input, envp);
		// int counter = -1;
		// while (args[++counter])
		// 	printf("%s\n", args[counter]);
		free(input);
		ft_freesplit(args);
	}
	return 0;
}
