#include "../../minishell.h"

t_command	*set_variables(t_command *command)
{
	t_command	*com;
	t_list		*lst;
	char 		*str;

	com = command;
	while (com)
	{
		lst = com->content;
		split_by_pattern(&lst, "$");
		while (lst)
		{
			str = lst->content;
			if (strchr(str, '$'))
			{
				printf("%s\n", (char *) lst->next->content);
			}
			lst = lst->next;
		}
		com = com->next;
	}
	return (command);
}

int	is_in_wildcard_templ(char *string, char *template)
{
	if (*template != '*')
	{
		if (*string)
		{
			if ((*template == '?' || *string == *template)
				&& is_in_wildcard_templ(string + 1, template + 1))
				return (1);
			return (0);
		}
		else
		{
			if (*template == '\0')
				return (1);
			return (0);
		}
	}
	else
	{
		if (is_in_wildcard_templ(string, template + 1)
			|| (*string != '\0' && is_in_wildcard_templ(string + 1, template)))
			return (1);
		return (0);
	}
}

t_list	*ft_list_files(char *name)
{
	DIR *d;
	t_list	*file_list;
	struct dirent *dir;

	file_list = NULL;
	d = opendir(name);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_name[0] != '.')
				ft_lstadd_back(&file_list, ft_lstnew(ft_strdup(dir->d_name)));
		}
		closedir(d);
	}
	return (file_list);
}

//int main(int argc, char **argv)
//{
////	ft_print_lst(ft_list_files(argv[1]));
//
//	return (0);
//}