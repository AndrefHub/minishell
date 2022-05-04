#include "../../minishell.h"

//char    **parse_to_lines(char *input)
//{
//    return (ft_split(input, '\n')); // for now. Need to add '\' functionality
//}
//
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
		i++;
	}
}
//
//char	**parse_quotes(char *string)
//{
//	char	**command;
//
//	while (command) {
//		int init_subshell(command);
//	}
//}

/*
 * true || echo "aaa" && echo "bbb"
 * [<true || echo >, <"aaa">, < && echo >, <"bbb">]
 *
 * (true || (echo aaa && echo bbb) | wc -l ); (echo >> text.txt)
 * [<true || (echo >, <"aaa">, < && echo >, <"bbb">, <) | wc -l ; echo >> text.txt>]
 *
 *
 * [<(>, <true || >, <)>]
 * [<(>, <echo >, <"aaa">, < && echo >, <"bbb">, <)>]
 * [< | wc -l ; echo >> text.txt>]
 *
 * [<(>, <true || >, <)>]
 * [<(>, <echo >, <"aaa">, < && echo >, <"bbb">, <)>]
 * [< | wc -l >, <;>]
 * [< echo >> text.txt>]
 *
 * [<(>, <true || >]
 * [<(>, <echo >, <"aaa">, < && echo >, <"bbb">, <)>]
 * [< | wc -l >, <;>]
 * [< echo >> text.txt>]
 * */

t_command	*ft_new_command(t_list *content)
{
	t_command	*command;

	command = (t_command *) malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->content = content;
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

int	ft_find_substr(const char *string, const char *sub)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	flag = 0;
	if (!string || !sub)
		return (-1);
	while (string[i + ft_strlen(sub) - 1])
	{
		j = 0;
		while (sub[j])
		{
			if (string[i + j] == sub[j])
				j++;
			else
				break ;
			if (sub[j] == 0)
				flag = 1;
		}
		if (flag == 1)
			break;
		i++;
	}
	if (!flag)
		return (-1);
	return (i);
}

/*t_list	*ft_split_str_in_lst(char *pattern, t_list *elem)
{
	t_list	*next;
	int		len;
	char	*str;
	int		i;

	if (!elem)
		return (NULL);
	str = elem->content;
	next = elem->next;
	elem->next = NULL;
	i = 0;
	len = ft_find_substr(str, pattern);
	if (len != -1)
		i = (int) ft_strlen(str);
	else if (len == 0)
		elem->content = ft_strdup(str);
	else
	{
		elem->content = ft_strdup(pattern);
		ft_lstadd_back(&elem, ft_lstnew(ft_strdup(pattern)));
	}
	while (str[i])
	{
		len = ft_find_substr(&str[i], pattern);
		if (len != -1)
		{
			if (len != 0 && i == 1)
				ft_lstadd_back(&elem, ft_lstnew(ft_strndup(&str[i], len)));
			ft_lstadd_back(&elem, ft_lstnew(ft_strdup(pattern)));
			i += len;
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
}*/

t_list	*ft_split_str_in_lst(char *pattern, t_list *elem)
{
	t_list	*next;
	int		len;
	char	*str;
	int		i;
	int mode;

	mode = (int) ft_strlen(pattern);
	if (!elem)
		return (NULL);
	str = elem->content;
	next = elem->next;
	elem->next = NULL;
	i = 0;
	len = ft_find_substr(str, pattern);
	if (len == -1 || (len == 0 && ft_strlen(str) == ft_strlen(pattern)))
		i = (int ) ft_strlen(str);
	else if (len == 0)
		elem->content = ft_strdup(pattern);
	else
	{
		elem->content = ft_strndup(str, len);
		ft_lstadd_back(&elem, ft_lstnew(ft_strdup(pattern)));
		i += len + mode;
	}
	while (str[i])
	{
		len = ft_find_substr(&str[i + ft_strlen(pattern) - mode], pattern);
		if (len != -1)
		{
			if (len != 0 && i != 1)
			{
				ft_lstadd_back(&elem, ft_lstnew(ft_strndup(&str[i], len)));
				ft_lstadd_back(&elem, ft_lstnew(ft_strdup(pattern)));
			}
			i += len + mode;
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

// int main(int argc, char **argv, char **envp) {
// 	t_list *elem;
// 	t_list *tmp;

// 	elem = ft_lstnew(ft_strdup("true || echo \"aaa\" && echo \"bbb\""));
// 	tmp = elem;

// 	while (tmp) {
// 		ft_split_str_in_lst("echo", tmp);
// 		ft_printf("%s\n", tmp->content);
// 		tmp = tmp->next;
// 	}
// 	ft_putendl_fd("++++++++++++++++++++++++++", 1);
// 	tmp = elem;
// 	while (tmp) {
// 		ft_split_str_in_lst("\"", tmp);
// 		ft_printf("%s\n", tmp->content);
// 		tmp = tmp->next;
// 	}
// }

// void	parse_parentheses(char *string)
// {
// 	char	**command;

// 	while (command) {
// 		int init_subshell(command);
// 	}
// }

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