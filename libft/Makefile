NAME    = libft.a
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -c
LFLAGS  = -Wall -Wextra -Werror -o
SRCDIR	= src/
SRCFILE	= ft_atoi.c			ft_strdup.c		ft_bzero.c		ft_striteri.c	\
		  ft_split.c		ft_isalnum.c	ft_strlcat.c	ft_calloc.c		\
          ft_isalpha.c		ft_memchr.c		ft_strlcpy.c	ft_strjoin.c	\
          ft_isascii.c		ft_memcmp.c		ft_strlen.c		ft_itoa.c		\
          ft_isdigit.c		ft_memcpy.c		ft_strmapi.c	ft_memset.c		\
          ft_isprint.c		ft_memmove.c	ft_strncmp.c	ft_strnstr.c	\
          ft_putchar_fd.c	ft_strrchr.c	ft_putendl_fd.c	ft_strchr.c		\
          ft_strtrim.c		ft_putnbr_fd.c	ft_substr.c		ft_putstr_fd.c	\
          ft_tolower.c		ft_toupper.c	get_next_line.c	get_next_line_utils.c
SRCS	= $(addprefix $(SRCDIR), $(SRCFILE))
OBJDIR	= obj/
OBJFILE = $(SRCFILE:.c=.o)
OBJS	= $(addprefix $(OBJDIR), $(OBJFILE))
RM      = rm -rf
HEADER  = libft.h

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $@ -include $(HEADER)

$(NAME): $(OBJS) $(HEADER)
	ar rcs $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
