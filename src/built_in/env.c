#include "../../minishell.h"

int env(char **envp)
{
	if (!envp)
		return (1);
	while (*envp)
	{
		ft_printf("%s\n", *envp++);
	}
	return (0);
}
