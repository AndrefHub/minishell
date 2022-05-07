#include "../minishell.h"

t_msh g_msh;

void	very_important_function(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
}

char	**make_sp_ops(void )
{
	char	**lst;

	lst = malloc(sizeof(*lst) * 10);
	lst[0] = ft_strdup(";");
	lst[1] = ft_strdup("&&");
	lst[2] = ft_strdup("||");
	lst[3] = ft_strdup("&");
	lst[4] = ft_strdup("|");
	lst[5] = ft_strdup("<<");
	lst[6] = ft_strdup(">>");
	lst[7] = ft_strdup("<");
	lst[8] = ft_strdup(">");
	lst[9] = NULL;
	return (lst);
}

void	set_g_msh(char **envp)
{
	g_msh.envp = envp;
	g_msh.sp_ops = make_sp_ops();
}

int main(int argc, char **argv, char **envp)
{
	char		*input;
	// t_command	*commands;
	// char	**args;
	// int		code;

	very_important_function(argc, argv, envp);
	set_g_msh(envp);
	while (1)
	{
		input = readline("ඞabobusඞ> ");
		add_history(input);
		// args = parser_old(input, envp);
		// code = executor(args);
		// if (code)
		// 	printf("Error code %d\n", code);
		parser(input);
		if (ft_strncmp("q", input, 1) == 0)
			exit(0);

		free(input);
		// ft_freesplit(args);
	}
	return 0;
}
