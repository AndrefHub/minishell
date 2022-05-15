/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:58:22 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 16:12:04 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include "libft/libft.h"
# define SEMICOLON		0x0	// ;
# define DOUBLE_AND		0x1	// &&
# define DOUBLE_OR		0x2	// ||
# define PIPELINE		0x3	// |
# define HEREDOC		0x4	// <<
# define REDIR_IN		0x5	// <
# define REDIR_OUT_AP	0x6	// >>
# define REDIR_OUT_TR	0x7	// >
# define ENDING_TYPE	0x8	//
# define MINISHELLNAME "\033[1;31mඞ\033[0mabobus\033[1;36mඞ\033[0m> "

typedef struct s_envp
{
	char	*key;
	char	*value;
}	t_envp;

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
	t_list	*envp;
	char	**cenvp;
	int		err_code;
	char	*err_text;
	int		last_ex_code;
	char	*pwd;
	char	**sp_ops;
}	t_msh;

typedef struct s_file
{
	char	*f_name;
	int		fd;
	int		mode;
}	t_file;

typedef struct s_command
{
	t_list				*content;
	char				**name_args;
	int					link_type;
	int					bracket_r;
	int					bracket_l;
	t_file				*infile;
	t_file				*outfile;
	struct s_command	*next;
}	t_command;

extern t_msh	g_msh;

# define FT_SPACE "\t "
# define SPCHARS "|&<>;"
/* Testing functions */
void		ft_print_com(t_command *elem);
void		ft_print_lst(t_list *elem);
/* Parsing */
char		**parse_to_lines(char *string);
t_list		*parse_quotes(char *input);
t_list		*parse_parentheses(t_list *quotes);
t_command	*parse_semicolon(t_list *parentheses);
t_command	*parse_special_characters(t_list *lst);
void		parse_brackets(t_command *cmd);
t_command	*parse_redirects(t_command *commands);
t_command	*set_variables(t_command *command);
void		ft_list_to_char_ptr(t_command *cmd);
void		convert_commands_to_char_ptrs(t_command *cmd);
t_list		*ft_split_str_in_lst(char *pattern, t_list *elem, int mode);
void		split_by_pattern(t_list **lst, char *pattern, int mode);
void		ft_com_rm_space(t_command *cmd);
t_list		*ft_rm_space(t_list **lst);
/* t_command structure tools */
t_command	*ft_new_command(t_list *content, int code);
void		ft_comadd_back(t_command **lst, t_command *elem);
t_command	*ft_command_last(t_command *command);
void		ft_comclear(t_command **com, int ind);
/* t_list structure tools */
t_list		*ft_lstnsplit(t_list **begin, int n);
t_list		*ft_lstat(t_list *lst, int n);
void		ft_lstadd_middle(t_list **lst, t_list *add_next, t_list *to_add);
/* ft_split tools */
int			is_in(char c, const char *charset);
size_t		command_words_count(char **args);
t_list		*ft_lst_delnext(t_list *prev, t_list *elem, t_list **lst,
				void (*del)(void *));
t_command	*ft_command_split(t_command **prev, t_command *to_split,
				int link_type);
char		**ft_split_space(char *s, char *set);
/* string tools */
char		*ft_strcat_delim(char *first, char delim, char *second);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strchr_num(const char *s, int c);
int			ft_arraylen(void **arr);
/* working with path */
t_list		*ft_list_files(char *name);
char		*find_binary(char *command);
void		start(char *input);
void		setup_term(void);
/* working with envp */
t_list		*parse_envp(char **arr);
char		*envp_get_key(t_list *env);
char		*envp_get_value(t_list *env);
t_envp		*make_envp_entry(char *arg);
void		set_envp_entry(t_envp *entry);
void		free_envp_entry(void *entry);
void		ft_increment_shlvl(void );
void		update_cenvp(void );
int			find_at_first(const char *string, char *pattern);
char		*ft_find_envp(char *parameter);
/* fd smth */
void		dup2_and_close(int from, int to);
void		init_t_pipe_fd(t_pipe_fd *fd_data);
void		reset_t_pipe_fd(t_pipe_fd *fd_data);
/* builtins */
int			execute_commands(t_command *cmd);
t_command	*pipeline(t_command *to_pipe);
int			check_for_built_in(char **args);
int			echo(char **argv);
int			env(void );
int			export(char **args);
int			unset(char **args);
int			pwd(void );
int			ft_chdir(char *dir);
int			msh_exit(char **argv);
/* Signals */
void		init_sig_handler(void (*handler) (int, siginfo_t *, void *));
void		parent_sig_handler(int sigsum, siginfo_t *sig, void *context);
void		child_sig_handler(int sigsum, siginfo_t *sig, void *context);
void		clear_term_signal(void );
void		print_nothing(int mode);
/* Start executing */
void		start_one_line(char *line);
int			choose_code(char *spop);
void		check_end_and_start_one_line(char *line);
int			execute(char **command);
int			heredoc(char *delim);
int			check_syntax(t_command *command);
/* Wildcards */
void		set_wildcards(t_command *command);
int			is_in_wildcard_templ(char *string, char *template);
t_list		*recursive_wild_path(char *wildcard, char *pwd, char *prev_dir);
/* Errors */
void		set_error_code(int wpid_ret);
int			fill_error(int code);
void		reset_errors(void);
/* Files */
void		open_files(t_command *command);
void		ft_free_file(t_file *file, int ind);
void		set_file_in_command(t_command *command, int link_type, t_list *tmp);
t_file		*ft_file_new(char *filename, int link_type);
int			is_file_open(t_file *file);


void	ft_com_rm_quotes(t_command *cmd, char *quote);
#endif
