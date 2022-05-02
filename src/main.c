#include "../minishell.h"

void	very_important_function(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
}

void	parser(char *input)
{
	char	**commands;
	int		i;

	i = 0;
	commands = parse_to_lines(input);
	while (commands[i])
	{
		parse_parentheses(commands[i]);
		i++;
	}
}

void	parse_parentheses(char *string)
{
	int	init_subshell(command);
}


int main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**args;

	very_important_function(argc, argv, envp);
	// rl_bind_key('\t', rl_complete); // Autocompletes user's input when tab is pressed
	while (1)
	{
		input = readline("ඞabobusඞ> ");
		add_history(input);
//		args = parser(input, envp);
		pareser(input);
		free(input);
		ft_freesplit(args);
	}
	return 0;
}
