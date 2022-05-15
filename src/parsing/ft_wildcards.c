/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:56:19 by lsherry           #+#    #+#             */
/*   Updated: 2022/05/15 17:32:17 by kdancy           ###   ########.fr       */
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
	if (path)
	{
		free(path);
		path = NULL;
	}
	if (wildcard)
	{
		free(wildcard);
		wildcard = NULL;
	}
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
	if (prev_dir)
	{
		free(prev_dir);
		prev_dir = NULL;
	}
	wild_free_tool(path, wildcard);
}

static void	wild_tool(t_list *tmp, char *pwd)
{
	if (pwd)
	{
		free(pwd);
		pwd = NULL;
	}
	if (tmp)
	{
		ft_lstclear(&tmp, free);
		tmp = NULL;
	}
}

t_list	*recursive_wild_path(char *wc, char *d, char *prev_dir)
{
	char	*p;
	t_list	*w;
	t_list	*tmp;
	t_list	*out;

	out = NULL;
	p = ft_strndup(wc, ft_find_substr(wc, "/"));
	w = passed_wildcard_files(p, d);
	tmp = w;
	if (ft_strlen(p) != ft_strlen(wc))
	{
		d = ft_strjoin_gnl(d, "/");
		while (w)
		{
			ft_lstadd_back(&out, recursive_wild_path(ft_strdup(wc + ft_strlen(p)
						+ 1), ftsj(d, w->content), ftsj(w->content, "/")));
			w = w->next;
		}
		wild_tool(tmp, NULL);
	}
	else
		ft_lstadd_back(&out, tmp);
	ft_add_path(out, prev_dir, wc, p);
	free(d);
	return (out);
}
