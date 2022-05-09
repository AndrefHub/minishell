#include "../../minishell.h"

char    **parse_to_lines(char *input)
{
    return (ft_split(input, '\n')); // for now. Need to add '\' functionality
}

t_command	*parser(char *input)
{
	t_command	*full_cmd;
	t_command	*cmd;
	t_list		*lst;
	char		**commands;
	int			i;
//	t_command	*com;

	i = 0;
	commands = parse_to_lines(input); // Maybe change '\n' to ' ' (?) Or parse to lines only after quotes
	full_cmd = NULL;
	while (commands[i])
	{
		lst = parse_quotes(commands[i]);
		lst = parse_parentheses(lst);
		cmd = parse_semicolon(lst);
		cmd = parse_special_characters(cmd);
//		split_by_pattern(&cmd->content, " ");
		ft_com_rm_space(cmd);
//		convert_commands_to_char_ptrs(cmd);
		ft_comadd_back(&full_cmd, cmd);
		i++;
	}
//			set_variables(com);
	ft_print_com(full_cmd);
	return (full_cmd);
}


t_list	*parse_parentheses(t_list *quotes)
{
	split_by_pattern(&quotes, "(");
	split_by_pattern(&quotes, ")");
	return (quotes);
}

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