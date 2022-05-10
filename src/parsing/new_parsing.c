#include "../../minishell.h"

char    **parse_to_lines(char *input)
{
    return (ft_split(input, '\n')); // for now. Need to add '\' functionality
}

void start_one_line(char *line)
{
	t_command	*cmd;
	t_list		*lst;

	lst = parse_quotes(line);
	lst = parse_parentheses(lst);
	cmd = parse_special_characters(lst);
	free(line);
	while (cmd)
	{
		set_variables(cmd); // before start process
		ft_com_rm_space(cmd);
//		if (!check_syntax(cmd))
//			return ;
		convert_commands_to_char_ptrs(cmd);
//		execute_command(cmd);
		ft_print_lst(cmd->content);
		cmd = cmd->next;
	}
}

void start_cycle(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		start_one_line(lines[i]);
		i++;
	}
}

void start(char *input)
{
	char		**commands;

	commands = parse_to_lines(input);
	if (!commands[1])
		start_one_line(commands[0]);
	else
		start_cycle(commands);
/*	while (commands[i])
	{
		lst = parse_quotes(commands[i]);
		lst = parse_parentheses(lst);
		cmd = parse_special_characters(lst);
//			set_variables(com); // before start process
//		ft_com_rm_space(cmd);
//		convert_commands_to_char_ptrs(cmd);
		ft_comadd_back(&full_cmd, cmd);
		i++;
	}*/
}

t_list	*parse_parentheses(t_list *quotes)
{
	split_by_pattern(&quotes, "(");
	split_by_pattern(&quotes, ")");
	return (quotes);
}