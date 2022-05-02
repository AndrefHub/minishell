#include "../minishell.h"

int	find_at_first(const char *string, char *pattern, int pattern_len)
{
	int i;
	int len;

	i = 0;
	if (!pattern || !string)
		return (0);
	len = (int) ft_strlen(pattern);
	if (len > pattern_len)
		len = pattern_len;
	while (i < len)
	{
		if (string[i] != pattern[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_find_envp(char *parameter, char **envp)
{
	int		i;
	char	*out;
	int		parameter_len;

	i = 0;
	out = ft_strchr(parameter, ' '); // <<< change ' ' to FT_SPACE
	if (out == NULL)
		parameter_len = ft_strlen(parameter);
	else
		parameter_len = (int)(out - parameter);
	while (envp[i])
	{
		if (find_at_first(envp[i], parameter, parameter_len))
		{
			out = ft_strdup(envp[i] + ft_strlen(parameter) + 1);
			return (out);
		}
		i++;
	}
	return ("");
}

/*
int main(int argc, char **argv, char **envp)
{
	(void ) argc;
	(void ) argv;
	printf("%s", ft_find_envp(argv[1], envp));

	return 0;
}
*/
