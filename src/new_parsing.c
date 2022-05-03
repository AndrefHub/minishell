#include "../minishell.h"

char    **parse_to_lines(char *input)
{
    return (ft_split(input, '\n')); // for now. Need to add '\' functionality
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

// int	init_subshell(char *string)
// {

// 	char	 **args;
// 	args = parse_quotes();
// 	char	**commands = divide_semicolon();
// 	t_command *lol = create_links(commands[i]);
// 	replace_dollar_and_star(lol);
// 	divide_on_name_and_args();
// 	execute_command();
// }