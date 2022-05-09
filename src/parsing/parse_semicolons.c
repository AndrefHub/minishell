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
	new_begin = lst;
	while (tmp)
	{
		++counter;
		if (ft_strncmp(((char *) tmp->content), pattern, ft_strlen(tmp->content)) == 0)
		{
			tmp = tmp->next;
			ft_comadd_back(&commands, ft_new_command(ft_lstnsplit(&new_begin, counter), link_type));
			counter = 0;
		}
		else
			tmp = tmp->next;
	}
	if (counter)
		ft_comadd_back(&commands, ft_new_command(new_begin, ENDING_TYPE));
	return (commands);
}

t_command	*parse_semicolon(t_list *parentheses)
{
	return (parse_pattern(parentheses, g_msh.sp_ops[SEMICOLON], SEMICOLON));
}

t_command	*ft_command_split(t_command **prev, t_command *to_split, int link_type)
{
	t_command	*commands;
	t_list		*splitted;
	t_list		*new_begin;
	t_list		*tmp;
	int			counter;
	
	counter = 0;
	commands = NULL;
	split_by_pattern(&(to_split->content), g_msh.sp_ops[link_type]);
	splitted = to_split->content;
	tmp = splitted;
	new_begin = tmp;
	while (tmp)
	{
		++counter;
		if (ft_strncmp(((char *) tmp->content), g_msh.sp_ops[link_type], ft_strlen(g_msh.sp_ops[link_type])) == 0)
		{
			tmp = tmp->next;
			ft_comadd_back(&commands, ft_new_command(ft_lstnsplit(&new_begin, counter), link_type));
			counter = 0;
		}
		else
			tmp = tmp->next;
	}
	if (counter)
	{
		to_split->content = new_begin;
		ft_comadd_back(&commands, to_split);
	}
	else
		ft_command_last(commands)->next = to_split->next;
	if (*prev)
		(*prev)->next = commands;
	return (commands);
}

t_command	*parse_special_characters(t_command *commands)
{
	t_command	*new_begin;
	t_command	*prev;
	t_command	*buffer;
	int			counter;

	prev = NULL;
	buffer = commands;
	counter = 0;
	while (++counter < 5)
	{
		prev = NULL;
		buffer = commands;
		while (commands)
		{
			if (commands == buffer)											// Check if *commands is the first element of the list.
				new_begin =	ft_command_split(&prev, commands, counter);		// If true, save new begin of the list to new_begin.
			else
				ft_command_split(&prev, commands, counter);
			prev = commands;
			commands = commands->next;
		}
		commands = new_begin;
	}
	return (new_begin);
}
