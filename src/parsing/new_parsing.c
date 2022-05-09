#include "../../minishell.h"

char    **parse_to_lines(char *input)
{
    return (ft_split(input, '\n')); // for now. Need to add '\' functionality
}

t_command	*parser(char *input)
{
	t_command	*full_cmd;
	t_command	*cmd;
	t_list		*lst;
	char		**commands;
	int			i;
	t_command	*com;

	i = 0;
	commands = parse_to_lines(input); // Maybe change '\n' to ' ' (?) Or parse to lines only after quotes
	full_cmd = NULL;
	while (commands[i])
	{
		lst = parse_quotes(commands[i]);
		lst = parse_parentheses(lst);
		cmd = parse_semicolon(lst);
//		cmd = get_full_command(cmd);
		cmd = parse_special_characters(cmd);
		com = cmd;
		while (com)
		{
			com = set_variables(cmd);
			com = com->next;
		}
		ft_comadd_back(&full_cmd, cmd);
		i++;
	}
	ft_print_com(full_cmd);
	return (full_cmd);
}

t_list	*ft_split_str_in_lst(char *pattern, t_list *elem)
{
	t_list	*next;
	int		len;
	int		i;
	char	*str;

	if (!elem)
		return (NULL);
	str = elem->content;
	len = ft_find_substr(str, pattern);
	if (!str || str[0] == '"' || str[0] == '\'' || str[ft_strlen(str)] == '"'
		|| str[ft_strlen(str)] == '\'' || len == -1
		|| (len == 0 && ft_strlen(str) == ft_strlen(pattern)))
		return (elem);
	next = elem->next;
	elem->next = NULL;
	if (len == 0)
		elem->content = ft_strdup(pattern);
	else
	{
		elem->content = ft_strndup(str, len);
		ft_lstadd_back(&elem, ft_lstnew(ft_strdup(pattern)));
	}
	i = len + (int) ft_strlen(pattern);
	while (str[i])
	{
		len = ft_find_substr(&str[i], pattern);
		if (len != -1)
		{
			if (len == 0)
				ft_lstadd_back(&elem, ft_lstnew(ft_strdup(pattern)));
			else
			{
				ft_lstadd_back(&elem, ft_lstnew(ft_strndup(&str[i], len)));
				ft_lstadd_back(&elem, ft_lstnew(ft_strdup(pattern)));
			}
			i += len + (int )ft_strlen(pattern);
		}
		else
		{
			ft_lstadd_back(&elem, ft_lstnew(ft_strdup(&str[i])));
			break ;
		}
	}
	free(str);
	ft_lstlast(elem)->next = next;
	return (elem);
}

t_list	*parse_parentheses(t_list *quotes)
{
	split_by_pattern(&quotes, "(");
	split_by_pattern(&quotes, ")");
	return (quotes);
}

// int	init_subshell(char *string)
// {
//
// 	char	 **args;
// 	args = parse_quotes();
// 	char	**commands = divide_semicolon();
// 	t_command *lol = create_links(commands[i]);
// 	replace_dollar_and_star(lol);
// 	divide_on_name_and_args();
// 	execute_command();
// }