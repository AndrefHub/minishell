#include "../../minishell.h"

char    **parse_to_lines(char *input)
{
	return (ft_split(input, '\n')); // for now. Need to add '\' functionality
}

// void	parser(char *input)
// {
// 	char	**commands;
// 	int		i;

// 	i = 0;
// 	commands = parse_to_lines(input);
// 	while (commands[i])
// 	{
// 		parse_parentheses(commands[i]);
// 		i++;
// 	}
// }

char	*get_quote(char **input)
{
	size_t	q;
	char	to_find;
	char	*remainder;

	to_find = '\'';
	q = ft_strchr_num(*input, '\'');
	if (q > ft_strchr_num(*input, '\"'))
	{
		q = ft_strchr_num(*input, '\"');
		to_find = '\"';
	}
	if (q == 0)
	{
		q = ft_strchr_num(*(input + 1), to_find) + 1 + 1; 
	}
	if (q > ft_strlen(*input))
		q = ft_strlen(*input);
	remainder = ft_strndup(*input, q);
	*input += q;
	return (remainder);
}

t_list	*parse_quotes(char *input)
{
	t_list	*quotes;
	t_list	*next;
	//char
	char	*tmp;

	quotes = ft_lstnew(NULL);
	tmp = input;
	while (ft_strlen(tmp))
	{
		printf("%zu\n", ft_strlen(tmp));
		ft_lstadd_back(&quotes, ft_lstnew(get_quote(&tmp)));
	}
	next = quotes->next;
	ft_lstdelone(quotes, free);
	return (next);
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

// 	char	 **args;
// 	args = parse_quotes();
// 	char	**commands = divide_semicolon();
// 	t_command *lol = create_links(commands[i]);
// 	replace_dollar_and_star(lol);
// 	divide_on_name_and_args();
// 	execute_command();
// }