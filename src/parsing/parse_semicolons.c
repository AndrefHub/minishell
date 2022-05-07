#include "../../minishell.h"

void	split_by_pattern(t_list **lst, char *pattern)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		ft_split_str_in_lst(pattern, tmp);
		tmp = tmp->next;
	}
}

t_command	*parse_pattern(t_list *lst, char *pattern, int link_type)
{
	t_command	*commands;
	t_list		*new_begin;
	t_list		*tmp;
	int			counter;
	
	counter = 0;
	commands = NULL;
	split_by_pattern(&lst, pattern);
	tmp = lst;
	new_begin = tmp;
	while (tmp)
	{
		++counter;
		if (ft_strncmp(((char *) tmp->content), pattern, ft_strlen(pattern)) == 0)
		{
			tmp = tmp->next;
			ft_comadd_back(&commands, ft_new_command(ft_lstnsplit(&new_begin, counter), link_type));
			counter = 0;
		}
		else
			tmp = tmp->next;
	}
	if (counter)
		ft_comadd_back(&commands, ft_new_command(new_begin, 0));
	return (commands);
}

t_command	*parse_semicolon(t_list *parentheses)
{
	return (parse_pattern(parentheses, g_msh.sp_ops[SEMICOLON], SEMICOLON));
}

t_command	*parse_special_characters(t_command *commands)
{
	int counter;
	t_command	*lol;
	t_command	*tmp;

	counter = 0;
	while (++counter < 5)
	{
		lol = NULL;
		tmp = commands;
		while (commands)
		{
			ft_comadd_back(&lol, parse_pattern(commands->content, g_msh.sp_ops[counter], counter));
			if (!commands->next)
				commands->next = NULL;
			commands = commands->next;
		}
		ft_comclear(&tmp);
		commands = lol;
	}
	return (commands);
}

// t_command	*parse_semicolon(t_list *parentheses)
// {
// 	t_command	*commands;
// 	t_list		*tmp;
// 	char		**spops;
// 	int			link_type;
// 	int			counter;
	
// 	link_type = -1;
// 	spops = g_msh.sp_ops;
// 	while (++link_type < ft_arraylen(spops))
// 	{
// 		counter = 0;
// 		commands = NULL;
// 		split_by_pattern(&parentheses, spops[link_type]);
// 		tmp = parentheses;
// 		while (tmp)
// 		{
// 			++counter;
// 			if (ft_find_substr((char *) tmp->content, spops[link_type]) >= 0)
// 			{
// 				((char *) tmp->content)[ft_strlen(tmp->content) - ft_strlen(spops[link_type])] = '\0';
// 				ft_comadd_back(commands, ft_new_command(ft_lstnsplit(parentheses, tmp, counter), 1 << link_type));
// 			}
// 			tmp = tmp->next;
// 		} 
// 	}
// }
