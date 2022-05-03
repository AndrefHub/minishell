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
	int		code;

	g_msh.envp = envp;
	very_important_function(argc, argv, envp);
	while (1)
	{
		input = readline("ඞabobusඞ> ");
		add_history(input);
		args = parser_old(input, envp);
		code = executor(args);
		if (code)
			printf("Error code %d\n", code);
		// parser(input);
		free(input);
		ft_freesplit(args);
	}
	return 0;
}
