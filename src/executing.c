#include "../minishell.h"

int executor(char **args)
{

	// args[0] = find_binary(args[0], envp);
	check_for_built_in(args);
}