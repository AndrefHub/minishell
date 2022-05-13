#include "../../minishell.h"

//static int	check_spops(char *str, char *pat)
//{
//	if (ft_strlen(pat) == 1)
//	{
//		if (str[0] == pat[0])
//			return (1);
//	}
//	if (ft_strlen(pat) == 2 )
//	{
//		if (str[0] == pat[0] && str[1] == pat[1])
//			return (1);
//	}
//	return (0);
//}

int	fill_error(int code)
{
	if (code == 0)
		g_msh.err_text = ft_strdup("syntax error near unexpected token ';'");
	if (code == 1)
		g_msh.err_text = ft_strdup("syntax error near unexpected token '&&'");
	if (code == 2)
		g_msh.err_text = ft_strdup("syntax error near unexpected token '||'");
	if (code == 3)
		g_msh.err_text = ft_strdup("syntax error near unexpected token '|'");
	if (code == 4 || code == 5)
		g_msh.err_text = ft_strdup("syntax error near unexpected token '>>' or '>'");
	if (code == 6 || code == 7)
		g_msh.err_text = ft_strdup("syntax error near unexpected token '<<' or '<'");
	if (code == 9)
		g_msh.err_text = ft_strdup("syntax error near unexpected token '(' or ')'");;
	g_msh.err_code = 258;
	return (0);
}

int	check_syntax(void)
{
	if (g_msh.err_code != 0 || g_msh.err_text != NULL)
	{
		ft_putendl_fd(g_msh.err_text, 2);
		g_msh.last_ex_code = g_msh.err_code;
		return (0);
	}
	return (1);
}