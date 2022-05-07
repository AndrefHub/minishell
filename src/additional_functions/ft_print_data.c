#include "../../minishell.h"

void	ft_print_lst(t_list *elem)
{
	while (elem)
	{
		ft_putstr_fd(elem->content, 1);
		ft_putstr_fd(" <<<<<\n", 1);
		elem = elem->next;
	}
}

void	ft_print_com(t_command *elem)
{
	while (elem)
	{
		ft_putendl_fd("command:", 1);
		ft_print_lst(elem->content);
		ft_putstr_fd("Link type: ", 1);
		ft_putnbr_fd(elem->link_type, 1);
		elem = elem->next;
	}
}