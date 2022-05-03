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
	char	**command;

	while (command) {
		int init_subshell(command);
	}
}

int	init_subshell(char *string)
{

	char	 **args;
	args = parse_quotes();
	char	**commands = divide_semicolon();
	t_command *lol = create_links(commands[i]);
	replace_dollar_and_star(lol);
	divide_on_name_and_args();
	execute_command();
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**args;

	g_msh.envp = envp;
	very_important_function(argc, argv, envp);
	while (1)
	{
		input = readline("ඞabobusඞ> ");
		add_history(input);
//		args = parser(input, envp);
		parser(input);
		free(input);
		ft_freesplit(args);
	}
	return 0;
}
