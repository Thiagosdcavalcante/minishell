NAME = minishell

FILES = srcs/main.c\
		srcs/builtins/builtins.c\
		srcs/utils/utils.c\
		srcs/utils/list_functions_parser.c\
		srcs/utils/list_functions_env.c\
		srcs/utils/list_functions_commands.c\
		srcs/utils/list_tokens.c\
		srcs/parser/parser.c\
		srcs/exec/exec_functions.c\
		srcs/parser/gambs.c\
		srcs/errors/errors.c\
		srcs/exec/exec.c\
		srcs/redirect/redirect.c\
		srcs/tree/tree.c\
		srcs/heredoc/heredoc.c

COMPILER = cc
LIBFT = ./libft/libft.a
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -g
LDFLAGS = -lreadline
INC = -I ./srcs/
OBJS = $(FILES:%.c=%.o)

all:$(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(COMPILER) $(CFLAGS) $(OBJS) $(INC) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	@make -C ./libft/ --no-print-directory

clean: libclean
	rm -f $(OBJS) $(OBJS_B)

libclean:
	@make clean -C ./libft --no-print-directory

fclean: clean libfclean

fclean: clean
	rm -f $(NAME)

libfclean:
	@make fclean -C ./libft --no-print-directory

re: fclean all

%.o: %.c
	@$(COMPILER) $(CFLAGS) -c $< -o $@

.PHONY: all bonus clean fclean re


