NAME    = minishell
CC      = gcc
FLAGS	= -Wall -Wextra -Werror
LFLAGS	= -lreadline -L./libft -lft
SRCDIR	= src/
SRCFILE	= parsing.c funny_functions.c ft_command_split.c ft_split.c
MAIN	= main.c
BONUS	= main_bonus.c
SRCS	= $(addprefix $(SRCDIR), $(SRCFILE))
OBJDIR	= obj/
OBJFILE = $(SRCFILE:.c=.o)
OBJMAIN = $(addprefix $(OBJDIR), $(MAIN:.c=.o))
OBJBNS	= $(addprefix $(OBJDIR), $(BONUS:.c=.o))
OBJS	= $(addprefix $(OBJDIR), $(OBJFILE))
RM      = rm -rf
LIBHDR  = libft/libft.h
PIPHDR  = minishell.h

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@  -include $(LIBHDR) -include $(PIPHDR)

$(NAME): $(OBJS) $(OBJMAIN) $(HEADER)
	@make -C libft
	$(CC) $(FLAGS) $(OBJS) $(OBJMAIN) $(LFLAGS) -o $(NAME)

bonus: $(OBJS) $(OBJBNS) $(HEADER)
	@make -C libft
	$(CC) $(FLAGS) -g $(OBJS) $(OBJBNS)  -o $(NAME)

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	@make -C libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
