#include "../../minishell.h"

char    **parse_to_lines(char *input)
{
    return (ft_split(input, '\n')); // for now. Need to add '\' functionality
}

void	parser(char *input)
{
	t_command	*cmd;
	t_list	*lst;
	char	**commands;
	int		i;

	i = 0;
	commands = parse_to_lines(input);
	while (commands[i])
	{
		lst = parse_quotes(commands[i]);
		lst = parse_parentheses(lst);
		cmd = parse_semicolon(lst);
		ft_print_com(cmd);
		i++;
	}
}

t_list	*ft_split_str_in_lst(char *pattern, t_list *elem)
{
	t_list	*next;
	int		len;
	char	*str;
	int		i;

	if (!elem)
		return (NULL);
	str = elem->content;
	len = ft_find_substr(str, pattern);
	if (str[0] == '"' || str[0] == '\'' || str[ft_strlen(str)] == '"'
		|| str[ft_strlen(str)] == '\'' || len == -1
		|| (len == 0 && ft_strlen(str) == ft_strlen(pattern)))
		return (elem);
	next = elem->next;
	elem->next = NULL;
	i = 0;
//	if (len == -1 || (len == 0 && ft_strlen(str) == ft_strlen(pattern)))
//		i = (int ) ft_strlen(str);
	if (len == 0)
		elem->content = ft_strdup(pattern);
	else
	{
		elem->content = ft_strndup(str, len);
		ft_lstadd_back(&elem, ft_lstnew(ft_strdup(pattern)));
		i += len + ft_strlen(pattern);
	}
	while (str[i])
	{
		len = ft_find_substr(&str[i], pattern);
		if (len != -1)
		{
			if (len != 0 && i != 1)
			{
				ft_lstadd_back(&elem, ft_lstnew(ft_strndup(&str[i], len)));
				ft_lstadd_back(&elem, ft_lstnew(ft_strdup(pattern)));
			}
			i += len + ft_strlen(pattern);
		}
		else
		{
			ft_lstadd_back(&elem, ft_lstnew(ft_strdup(&str[i])));
			break ;
		}
	}
	if (!(len == -1 || (len == 0 && ft_strlen(str) == ft_strlen(pattern))))
		free(str);
	ft_lstlast(elem)->next = next;
	return (elem);
}

t_list	*parse_parentheses(t_list *quotes)
{
	t_list	*elem;

	elem = quotes;
	while (elem)
	{
		ft_split_str_in_lst("(", elem);
		elem = elem->next;
	}
	elem = quotes;
	while (elem)
	{
		ft_split_str_in_lst(")", elem);
		elem = elem->next;
	}
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