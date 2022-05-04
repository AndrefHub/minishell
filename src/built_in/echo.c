#include "../../minishell.h"

int echo(char **argv)
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

int msh_exit(char **argv)
{
	(void)argv;
	exit(0);
	return (0);
}