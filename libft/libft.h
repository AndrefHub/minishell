/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andref <andref@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:41:51 by kdancy            #+#    #+#             */
/*   Updated: 2021/11/20 15:41:48 by andref           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

//get_next_line begin
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

typedef struct s_buff
{
	char			*buff;
	int				fd;
	size_t			length;
	ssize_t			bytes_read;
	struct s_buff	*next;
}	t_buff;

size_t		ft_strchr_i(const char *s, int c);

void		free_fd_buff(t_buff **head, int fd);

t_buff		*ft_buff_new(int fd);

t_buff		*ft_buff_fd(int fd, t_buff **buff);

void		ft_readnew(t_buff **fd_buffer);

char		*realloc_end(t_buff **fd_buffer, size_t new_begin);

char		*get_next_line(int fd);
//get_next_line end
int			is_in_set(char c, char *set);

void		*ft_memset(void *s, int c, size_t n);

void		ft_bzero(void *s, size_t n);

void		*ft_memcpy(void *dest, const void *src, size_t n);

void		*ft_memmove(void *dest, const void *src, size_t n);

void		*ft_memchr(const void *s, int c, size_t n);

int			ft_memcmp(const void *s1, const void *s2, size_t n);

size_t		ft_strlen(const char *s);

size_t		ft_strclen(char const *s, char c);

size_t		ft_strlcpy(char *dest, const char *src, size_t size);

size_t		ft_strlcat(char *dest, const char *src, size_t size);

char		*ft_strchr(const char *s, int c);

char		*ft_strrchr(const char *s, int c);

char		*ft_strnstr(char *haystack, char *needle, size_t len);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			ft_atoi(const char *str);

int			ft_isalpha(int c);

int			ft_isdigit(int c);

int			ft_isalnum(int c);

int			ft_isascii(int c);

int			ft_isprint(int c);

int			ft_toupper(int c);

int			ft_tolower(int c);

void		*ft_calloc(size_t count, size_t size);

char		*ft_strdup(const char *s);

char		*ft_substr(char const *s, size_t start, size_t len);

char		*ft_strjoin(char const *s1, char const *s2);

char		*ft_strtrim(char const *s1, char const *set);

char		**ft_split(char const *s, char c);

void		*ft_freesplit(char **words);

char		*ft_itoa(int n);

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void		ft_striteri(char *s, void (*f)(unsigned int, char*));

void		ft_putchar_fd(char c, int fd);

void		ft_putstr_fd(char *s, int fd);

void		ft_putendl_fd(char *s, int fd);

void		ft_putnbr_fd(int n, int fd);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

t_list		*ft_lstnew(void *content);

int			ft_lstsize(t_list *lst);

t_list		*ft_lstlast(t_list *lst);

void		ft_lstdelone(t_list *lst, void (*del)(void *));

void		ft_lstclear(t_list **lst, void (*del)(void *));

void		ft_lstiter(t_list *lst, void (*f)(void *));

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
