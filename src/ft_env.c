#include "../minishell.h"

int ft_env(char **envp)
{
	if (!envp)
		return (1);
	while (*envp)
	{
		ft_printf("%s\n", *envp++);
	}
	return (0);
}

/*
int main(int argc, char **argv, char **envp)
{
	ft_env(envp);
	return (0);
}*/
