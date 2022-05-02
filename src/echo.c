#include "../minishell.h"

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
	return (1);
}

int echo(int argc, char **argv)
{
	int flag;
	int	i;

	flag = 1;
	i = 0;
	if (find_at_first(argv[1], "-n"))
	{
		argv++;
		flag = 0;
	}
	while (*++argv)
	{
		ft_printf("%s", *argv);
		if (*(argv + 1))
			ft_printf(" ");
	}
	if (flag)
		printf("\n");
	return (0);
}
