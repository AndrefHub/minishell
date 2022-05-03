#include "../../minishell.h"

int	find_at_first(const char *string, char *pattern)
{
	int i;
	int len;

	i = 0;
	if (!pattern || !string)
		return (0);
	len = (int) ft_strlen(pattern);
	while (i < len)
	{
		if (string[i] != pattern[i])
			return (0);
		i++;
	}
	if (ft_strchr("=", string[i]))
		return (1);
	return (0);
}

char	*ft_find_envp(char *parameter, char **envp)
{
	int		i;
	char	*out;

	i = 0;
	while (envp[i])
	{
		if (find_at_first(envp[i], parameter))
		{
			out = ft_strdup(envp[i] + ft_strlen(parameter) + 1);
			return (out);
		}
		i++;
	}
	return (ft_strdup(""));
}
