#include "../../minishell.h"

t_envp	*make_envp_entry(char *arg)
{
	t_envp	*entry;
	char	**splitted;

	entry = malloc(sizeof(*entry));
    splitted = ft_split_space(arg, "=");
	entry->key = ft_strdup(splitted[0]);
    if (ft_arraylen((void *)splitted) == 1)
        entry->value = NULL;
    else
        entry->value = ft_strdup(splitted[1]);
	ft_freesplit(splitted);
	return (entry);
}

t_list	*parse_envp(char **arr)
{
	t_list	*envp;
	int		counter;

	envp = NULL;
	counter = -1;
	while (arr[++counter])
		ft_lstadd_back(&envp, ft_lstnew(make_envp_entry(arr[counter])));
	return (envp);
}

char	*envp_get_key(t_list *env)
{
	return (((t_envp *)env->content)->key);
}

char	*envp_get_value(t_list *env)
{
	return (((t_envp *)env->content)->value);
}

void	update_cenvp()
{
	char	**cenvp;
	t_list	*envp;
	int		counter;

	envp = g_msh.envp;
	cenvp = malloc(sizeof(*cenvp) * (ft_lstsize(envp) + 1));
	counter = 0;
	while (envp)
	{
		cenvp[counter] = ft_strcat_delim(envp_get_key(envp), '=',
			envp_get_value(envp));
		++counter;
		envp = envp->next;
	}
	free(g_msh.cenvp);
	g_msh.cenvp = cenvp;
}