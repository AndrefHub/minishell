#include "../../minishell.h"

void	ft_list_to_char_ptr(t_command *cmd)
{
	int		counter;
	int		arrsize;
	t_list	*local_copy;

	local_copy = cmd->content;
	arrsize = ft_lstsize(local_copy)
	cmd->name_args = malloc(sizeof(*(cmd->name_args)) * (arrsize + 1));
	counter = -1;
	while (++counter < arrsize)
	{
		cmd->name_args[counter] = (char *)(local_copy->content);
		local_copy = local_copy->next;
	}
	cmd->name_args[counter] = NULL;
}

void	convert_commands_to_char_ptrs(t_command *cmd)
{
	t_command	*local_copy;

	while (local_copy)
	{
		ft_list_to_char_ptr(local_copy);
		local_copy = local_copy->next;
	}
}