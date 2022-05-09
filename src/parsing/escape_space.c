#include "../../minishell.h"

t_command	*ft_rm_space(t_command *cmd)
{
	t_list		*lst;
	t_command	*command;

	command = cmd;
	while(command)
	{
		lst = command->content;
		while (lst)
		{

			lst = lst->next;
		}
		command = command->next;
	}
}