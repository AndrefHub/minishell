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

t_list	*ft_lstnsplit(t_list *begin_, t_list *lst, int n)
{
	// t_list	*begin;
	// t_list	*cocks;

	// begin = lst;
	//*lst = ft_lstat(*lst, n);
	ft_lstat(begin_, n - 1)->next = NULL;
	return (lst);
}

void	split_by_semicolons(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		ft_split_str_in_lst(";", tmp);
		tmp = tmp->next;
	}
}

t_command	*parse_semicolon(t_list *parentheses)
{
	t_command	*commands;
	t_list		*tmp;
	int			counter;

	counter = 0;
	commands = NULL;
	split_by_semicolons(&parentheses);
	tmp = parentheses;
	while (tmp)
	{
		++counter;
		if (ft_strchr((char *) tmp->content, ';'))
		{
			ft_comadd_back(commands, ft_new_command(ft_lstnsplit(parentheses, tmp, counter), SEMICOLON));
		}
		tmp = tmp->next;
	} 
}