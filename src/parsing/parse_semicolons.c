#include "../../minishell.h"

t_list	*ft_lstat(t_list *lst, int n)
{
	int	counter;

	counter = -1;
	while (++counter < n && lst)
	{
		lst = lst->next;
	}
	return (lst);
}

t_list	*ft_lstnsplit(t_list **begin, int n)
{
	// t_list	*begin;
	t_list	*cocks;

	cocks = *begin;
	*begin = ft_lstat(*begin, n);
	ft_lstat(cocks, n - 1)->next = NULL;
	return (cocks);
}

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

t_command	*parse_semicolon(t_list *parentheses)
{
	t_command	*commands;
	t_list		*new_begin;
	t_list		*tmp;
	int			counter;
	
	counter = 0;
	commands = NULL;
	split_by_pattern(&parentheses, ";");
	tmp = parentheses;
	new_begin = tmp;
	while (tmp)
	{
		++counter;
		if (ft_find_substr((char *) tmp->content, ";") >= 0)
		{
			tmp = tmp->next;
			ft_comadd_back(&commands, ft_new_command(ft_lstnsplit(&new_begin, counter), SEMICOLON));
			counter = 0;
//			new_begin = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	ft_comadd_back(&commands, ft_new_command(new_begin, 0));
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