#include "../../minishell.h"

t_command	*ft_new_command(t_list *content, int code)
{
	t_command	*command;

	command = (t_command *) malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->content = content;
	command->link_type = code;
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

void	ft_comclear(t_command **com)
{
	t_command	*elem;
	t_command	*copy;

	copy = *com;
	while (copy)
	{
		elem = copy->next;
		if (copy->content)
			ft_lstclear(&(copy->content), free);
		free(copy);
		copy = elem;
	}
	*com = ((void *)0);
}