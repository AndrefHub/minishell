#include "../../minishell.h"

int	check_spops(char *str, int mode)
{
	int	i;

	i = mode;
	while (i != 9)
	{
		if (ft_find_substr(str, g_msh.sp_ops[i]))
			return (i);
		i++;
	}
	return (-1);
}

// int	check_syntax(t_command *cmd)
// {
// 	t_list	*lst;
// 	int		redir;
// 	int		i;

// 	lst = cmd->content;
// 	i = check_spops(lst->content, 0);
// 	if (i != -1)
// 	{
// 		g_msh.err_code = 258;
// 		g_msh.err_text = ft_strdup("syntax error near unexpected token ");
// 		return (0);
// 	}
// 	lst = lst->next;
// 	while (lst)
// 	{
// 		i = check_spops(lst->content, 5);
// 		if (i != -1)
// 			break ;
// 		lst = lst->next;
// 	}


// }