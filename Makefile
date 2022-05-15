NAME    = minishell
CC      = gcc
FLAGS	= -Wall -Wextra -Werror -g
LFLAGS	= -lreadline -L./libft -lft
SRCDIR	= src/
READLINE_FLAGS = -I/usr/local/opt/readline/include
SRCFILE	=	additional_functions/ft_command_split.c\
			additional_functions/ft_envparam.c\
			additional_functions/ft_split.c\
			additional_functions/funny_functions.c\
			additional_functions/ft_print_data.c\
			additional_functions/ft_command_list.c\
			additional_functions/ft_split_str_in_lst.c\
			additional_functions/ft_list_to_char.c\
			additional_functions/parse_envp.c\
			built_in/built_in_commands.c\
			built_in/echo.c\
			built_in/env.c\
			built_in/chdir.c\
			built_in/export.c\
			built_in/unset.c\
			built_in/pwd.c\
			executing/errors.c\
			executing/heredoc.c\
			executing/executing.c\
			executing/file.c\
			executing/pipeline.c\
			executing/open_files.c\
			signals/sig_handler.c\
			signals/term_printing.c\
			parsing/ft_wildcards.c\
			parsing/parse_quotes.c\
			parsing/parsing.c\
			parsing/parse_semicolons.c\
			parsing/set_variables.c\
			parsing/escape_space.c\
			parsing/parse_parentheses.c
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
MSHHDR  = minishell.h

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(MSHHDR)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)additional_functions
	@mkdir -p $(OBJDIR)built_in
	@mkdir -p $(OBJDIR)executing
	@mkdir -p $(OBJDIR)parsing
	@mkdir -p $(OBJDIR)signals
	@$(CC) $(FLAGS) $(READLINE_FLAGS) -c $< -o $@  -include $(LIBHDR) -include $(MSHHDR)
	@printf "\033[1;36m/\033[0m"

$(NAME): $(OBJS) $(OBJMAIN) $(MSHHDR)
	@echo
	@echo "\033[1;33m"$(NAME) "objs is up to date."'\033[0m'
	@make -C libft
	@$(CC) $(FLAGS) $(OBJS) $(OBJMAIN) $(LFLAGS) -o $(NAME)
	@echo "\033[1;33m"$(NAME) "is up to date."'\033[0m'

clean:
	@$(RM) $(OBJDIR)
	@echo '\033[1;31m'$(NAME) "objs deleted."'\033[0m'

fclean: clean
	@make -C libft fclean
	@$(RM) $(NAME)
	@echo '\033[1;31m'$(NAME) "deleted."'\033[0m'

re: fclean all

.PHONY: all clean fclean re bonus
