#include "../../minishell.h"

t_list	*parse_parentheses(t_list *quotes)
{
	split_by_pattern(&quotes, "(");
	split_by_pattern(&quotes, ")");
	return (quotes);
}

void	parse_brackets(t_command *cmd)
{
	t_command	*command;
	t_list		*elem;
	t_list		*prev;
	int			br_r;
	int			br_l;

	br_l = 0;
	br_r = 0;
	command = cmd;
	prev = NULL;
	while (command)
	{
		command->bracket_r = 0;
		command->bracket_l = 0;
		elem = command->content;
		while (elem)
		{
			if (ft_strchr("(", ((char *)elem->content)[0]))
			{
				command->bracket_l++;
				br_l++;
				elem = ft_lst_delnext(prev, elem, &command->content);
				if (elem && ft_strchr(")", ((char *)elem->content)[0]))
					fill_error(9);
			}
			else if (ft_strchr(")", ((char *)elem->content)[0]))
			{
				command->bracket_r++;
				br_r++;
				elem = ft_lst_delnext(prev, elem, &command->content);
				if (elem && ft_strchr("(", ((char *)elem->content)[0]))
					fill_error(9);
			}
			else
			{
				prev = elem;
				elem = elem->next;
			}
		}
		if (command->bracket_l > 0 && command->bracket_r > 0)
		{
			if (command->bracket_r > command->bracket_l)
			{
				command->bracket_r -= command->bracket_l;
				command->bracket_l = 0;
			}
			else
			{
				command->bracket_l -= command->bracket_r;
				command->bracket_r = 0;
			}
		}
		command = command->next;
	}
	if (br_l - br_r != 0)
		fill_error(9);
}