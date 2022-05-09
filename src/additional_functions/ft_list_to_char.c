#include "../../minishell.h"

void	ft_list_to_char_ptr(t_command *cmd)
{
	int		counter;
	int		arrsize;
	t_list	*local_copy;

	local_copy = cmd->content;
	arrsize = ft_lstsize(local_copy)
	cmd->cmd = malloc(sizeof(*(cmd->cmd)) * (arrsize + 1));
	counter = -1;
	while (++counter < arrsize)
	{
		cmd->cmd[counter] = (char *)(local_copy->content);
		local_copy = local_copy->next;
	}
	cmd->cmd[counter] = NULL;
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