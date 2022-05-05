#ifndef MINISHELL_H
# define MINISHELL_H

// с1 && с2  -	выполняет c1 в обычном режиме,
//				выполняет с2 в обычном режиме только если успешно отработала с1

// с1 || с2  -	выполняет c1 в обычном режиме,
//				выполняет с2 в обычном режиме только если с1 экстренно завершилась

// c1 & c2   -	выполняет c1 в бэкграунде (т.е. не может принимать ввод с терминала),
//				выполняет с2 одновременно с с1 в обычном режиме

// с1 | с2   -	одновременно выполняет с1 и с2 в обычном режиме,
//				вывод с1 соединен с вводом с2

// с1 < input    -	заменяет ввод с1 на содержимое файла input

// с1 > output   -	перенаправляет вывод с1 в файл output, 
//					создает output, если он не существует 
//					перезаписывает содержимое файла output в ином случае

// с1 >> output  -	перенаправляет вывод с1 в файл output, 
//					создает output, если он не существует 
//					дозаписывает вывод с1 в файл output в ином случае

// с1 << input	 -	heredoc

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "libft/libft.h"
/*
# ifdef COLORED_TEXT

#  define COLOR_RED		"\033[1;31m"
#  define COLOR_GREEN	"\033[1;32m"
#  define COLOR_YELLOW	"\033[1;33m"
#  define COLOR_BLUE	"\033[1;34m"
#  define COLOR_CYAN	"\033[1;36m"
#  define COLOR_RESET	"\033[0m"

# else

#  define COLOR_RED		""
#  define COLOR_GREEN	""
#  define COLOR_YELLOW	""
#  define COLOR_BLUE	""
#  define COLOR_CYAN	""
#  define COLOR_RESET	""

# endif
*/

# define SEMICOLON		0x0	// ;
# define DOUBLE_AND		0x1	// &&
# define DOUBLE_OR		0x2	// ||
# define HEREDOC		0x3	// <<
# define REDIR_OUT_AP	0x4	// >>
# define SINGLE_AND		0x5	// &
# define PIPELINE		0x6	// |
# define REDIR_IN		0x7	// <
# define REDIR_OUT_TR	0x8	// >

// # define SEMICOLON		0x001	// ;
// # define DOUBLE_AND		0x002	// &&
// # define DOUBLE_OR		0x004	// ||
// # define HEREDOC		0x008	// <<
// # define REDIR_OUT_AP	0x010	// >>
// # define SINGLE_AND		0x020	// &
// # define PIPELINE		0x040	// |
// # define REDIR_IN		0x080	// <
// # define REDIR_OUT_TR	0x100	// >

# define PARSER_SINGLE_Q_FLAG 1
# define PARSER_DOUBLE_Q_FLAG 2

typedef struct s_spop
{
	char	*sp_operator;
	int		code;
}	t_spop;

typedef struct s_msh 
{
    char	**envp;
	int		err_code;
	char	*curr_dir;
	char	**sp_ops;
}	t_msh;

typedef struct s_command
{
	t_list 				*content;
	int					link_type;
	struct s_command	*next;
}	t_command;

typedef	struct s_file
{
	int		mode;
	char	*f_name;
}	t_file;

typedef struct s_input
{
	char		*input;
	char		**lines;
	char		**quotes;
	t_command	*brackets;
}	t_input;

t_msh g_msh;

# define FT_SPACE "\t "
# define FT_DELIM "|&<>"

void	ft_print_com(t_command *elem);
void	ft_print_lst(t_list *elem);

char 		**parse_to_lines(char *string);
t_list		*parse_quotes(char *input);
t_list		*parse_parentheses(t_list *quotes);
t_command   *parse_semicolon(t_list *parentheses);

t_list		*ft_split_str_in_lst(char *pattern, t_list *elem);

t_command	*ft_new_command(t_list *content, int code);
void		ft_comadd_back(t_command **lst, t_command *new);
t_command	*ft_command_last(t_command *command);

int		is_in(char c, char *set);
size_t	command_words_count(char **args);
char	**ft_command_split(char **args);
char	**ft_split_space(char *s, char *set);

char	*ft_strcat_delim(char *first, char delim, char *second);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s, size_t n);
size_t	ft_strchr_num(const char *s, int c);
int 	ft_arraylen(void **arr);

char	**get_path(char **envp);
char	*find_binary(char *command, char **envp);
char	**parser_old(char *input, char **envp);
void	parser(char *input);
void 	pipex(char *input, char **envp);

int 	find_at_first(const char *string, char *pattern);
char	*ft_find_envp(char *parameter, char **envp);

int     check_for_built_in(char **args);
int		executor(char **args);

// echo.c
int     echo(char **argv);
int		env(char **envp);
int		msh_exit(char **argv);


#endif