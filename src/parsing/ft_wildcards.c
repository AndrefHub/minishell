/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:56:19 by lsherry           #+#    #+#             */
/*   Updated: 2022/05/14 19:56:20 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list	*passed_wildcard_files(char *wildcard, char *pwd)
{
	t_list	*file_list;
	t_list	*passed;
	t_list	*elem;

	file_list = ft_list_files(pwd);
	passed = NULL;
	elem = file_list;
	while (elem)
	{
		if (is_in_wildcard_templ(elem->content, wildcard))
			ft_lstadd_back(&passed, ft_lstnew(ft_strdup(elem->content)));
		elem = elem->next;
	}
	ft_lstclear(&file_list, free);
	return (passed);
}

static void	wild_free_tool(char *path, char *wildcard)
{
	free(path);
	free(wildcard);
}

static void	ft_add_path(t_list *out, char *prev_dir, char *wildcard, char *path)
{
	char	*str;

	while (out)
	{
		str = ft_strjoin(prev_dir, out->content);
		free(out->content);
		out->content = str;
		out = out->next;
	}
	free(prev_dir);
	wild_free_tool(path, wildcard);
}

static void	wild_tool(t_list *tmp, char *pwd)
{
	free(pwd);
	ft_lstclear(&tmp, free);
}

t_list	*recursive_wild_path(char *wildcard, char *pwd, char *prev_dir)
{
	char	*path;
	t_list	*wilds;
	t_list	*tmp;
	t_list	*out;

	out = NULL;
	path = ft_strndup(wildcard, ft_find_substr(wildcard, "/"));
	wilds = passed_wildcard_files(path, pwd);
	tmp = wilds;
	if (ft_strlen(path) != ft_strlen(wildcard))
	{
		pwd = ft_strjoin_gnl(pwd, "/");
		while (wilds)
		{
			ft_lstadd_back(&out, recursive_wild_path(ft_strdup(&wildcard
					[ft_strlen(path) + 1]), ft_strjoin(pwd, wilds->content),
					ft_strjoin(wilds->content, "/")));
			wilds = wilds->next;
		}
		wild_tool(tmp, pwd);
	}
	else
		ft_lstadd_back(&out, tmp);
	ft_add_path(out, prev_dir, wildcard, path);
	return (out);
}
