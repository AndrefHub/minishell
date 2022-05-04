#include "../../minishell.h"

//char    **parse_to_lines(char *input)
//{
//    return (ft_split(input, '\n')); // for now. Need to add '\' functionality
//}
//
//void	parser(char *input)
//{
//	char	**commands;
//	int		i;
//
//	i = 0;
//	commands = parse_to_lines(input);
//	while (commands[i])
//	{
//		parse_quotes();
//		i++;
//	}
//}
//
//char	**parse_quotes(char *string)
//{
//	char	**command;
//
//	while (command) {
//		int init_subshell(command);
//	}
//}

/*
 * true || echo "aaa" && echo "bbb"
 * [<true || echo >, <"aaa">, < && echo >, <"bbb">]
 *
 * true || (echo aaa && echo bbb)
 * [<true || (echo >, <"aaa">, < && echo >, <"bbb">, <)>]
 *
 *
 * [<true || >]
 * [<(>, <echo >, <"aaa">, < && echo >, <"bbb">, <)>]
 * */

t_command	*ft_new_command(t_list *content)
{
	t_command	*command;

	command = (t_command *) malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->content = content;
	command->next = NULL;
	return (command);
}

void	ft_comadd_back(t_command **lst, t_command *new)
{
	t_command	*elem;

	if (*lst)
	{
		elem = *lst;
		while (elem->next)
			elem = elem->next;
		elem->next = new;
	}
	else
		*lst = new;
}

t_command	*ft_command_last(t_command *command)
{
	if (!command)
		return (NULL);
	while (command->next)
		command = command->next;
	return (command);
}

t_command	*parse_parentheses(t_list *quotes, int k)
{

}

// void	parse_parentheses(char *string)
// {
// 	char	**command;

// 	while (command) {
// 		int init_subshell(command);
// 	}
// }

// int	init_subshell(char *string)
// {
//
// 	char	 **args;
// 	args = parse_quotes();
// 	char	**commands = divide_semicolon();
// 	t_command *lol = create_links(commands[i]);
// 	replace_dollar_and_star(lol);
// 	divide_on_name_and_args();
// 	execute_command();
// }