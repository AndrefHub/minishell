/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:58:22 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/10 19:51:00 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/wait.h>
#include <sys/ioctl.h>
# include <dirent.h>
# include <sys/types.h>
#include <termios.h>
# include <unistd.h>
#include <signal.h>
# include "libft/libft.h"
/*
# ifdef COLORED_TEXT

#  define COLOR_RED		"\033[1;31m"
#  define COLOR_GREEN	"\033[1;32m"
#  define COLOR_YELLOW	"\033[1;33m"
#  define COLOR_BLUE	"\033[1;34m"
#  define COLOR_CYAN	"\033[1;36m"
#  define COLOR_RESET	"\033[0m"

# endif
*/

# define SEMICOLON		0x0	// ;
# define DOUBLE_AND		0x1	// &&
# define DOUBLE_OR		0x2	// ||
# define SINGLE_AND		0x3	// &
# define PIPELINE		0x4	// |
# define HEREDOC		0x5	// <<
# define REDIR_OUT_AP	0x6	// >>
# define REDIR_IN		0x7	// <
# define REDIR_OUT_TR	0x8	// >
# define ENDING_TYPE	0x9	//

# define MINISHELLNAME "\033[1;31mඞ\033[0mabobus\033[1;36mඞ\033[0m> "

typedef struct s_pipe_fd
{
	int	fd_in;
	int	fd_out;
	int	pipe_fds[2];
	int	stdin_res;
	int	stdout_res;
}	t_pipe_fd;

typedef struct s_msh 
{
    char	**envp;
	int		err_code;
	char	*err_text;
	int		last_ex_code;
	char	*curr_dir;
	char	**sp_ops;
}	t_msh;

typedef struct s_command
{
	t_list 				*content;
	char				**name_args;
	int					link_type;

	struct s_command	*next;
}	t_command;

typedef	struct s_file
{
	char	*f_name;
	int		mode;
	struct s_file *next;
}	t_file;

typedef struct s_input
{
	char		*input;
	char		**lines;
	char		**quotes;
	t_command	*brackets;
}	t_input;

extern t_msh g_msh;

# define FT_SPACE "\t "
# define FT_DELIM "|&<>"

void	ft_print_com(t_command *elem);
void	ft_print_lst(t_list *elem);
/* Parsing */
char 		**parse_to_lines(char *string);
t_list		*parse_quotes(char *input);
t_list		*parse_parentheses(t_list *quotes);
t_command   *parse_semicolon(t_list *parentheses);
t_command	*parse_special_characters(t_list *lst);
t_command	*set_variables(t_command *command);
void		convert_commands_to_char_ptrs(t_command *cmd);

t_list		*ft_split_str_in_lst(char *pattern, t_list *elem);
void		split_by_pattern(t_list **lst, char *pattern);
void		ft_com_rm_space(t_command *cmd);
t_list		*ft_rm_space(t_list **lst);

/* t_command structure tools */
t_command	*ft_new_command(t_list *content, int code);
void		ft_comadd_back(t_command **lst, t_command *new);
t_command	*ft_command_last(t_command *command);
void		ft_comclear(t_command **com);

/* t_list structure tools */
t_list		*ft_lstnsplit(t_list **begin, int n);
t_list		*ft_lstat(t_list *lst, int n);

/* ft_split tools */
int     	is_in(char c, const char *charset);
size_t		command_words_count(char **args);
t_command	*ft_command_split(t_command **prev, t_command *to_split, int link_type);
char		**ft_split_space(char *s, char *set);

/* string tools */
char		*ft_strcat_delim(char *first, char delim, char *second);
int			ft_strcmp(const char *s1, const char *s2);

size_t		ft_strchr_num(const char *s, int c);
int 		ft_arraylen(void **arr);

/* working with path */
t_list		*ft_list_files(char *name);
char		*find_binary(char *command);
void		start(char *input);
void 		setup_term(void);

/* working with envp */
int 		find_at_first(const char *string, char *pattern);
char		*ft_find_envp(char *parameter, char **envp);

/* builtins */
int			execute_commands(t_command *cmd);
t_command	*pipeline(t_command *to_pipe);
int     	check_for_built_in(char **args);
int     	echo(char **argv);
int			env(char **envp);
int			msh_exit(char **argv);

void		init_sig_handler(void (*handler) (int, siginfo_t *, void *));
void		parent_sig_handler(int sigsum, siginfo_t *sig, void *context);
void		child_sig_handler(int sigsum, siginfo_t *sig, void *context);

void		print_nothing(int mode);
void		clear_term_signal(void );

int			execute(char **command);

#endif
