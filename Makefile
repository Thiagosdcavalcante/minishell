NAME	:= minishell

CC		:= cc

CFLAGS	:= -Wall -Wextra -Werror -g3

HEADERS	:= -I includes -I libs/libft

LIBFT	:= libs/libft/libft.a

SRC		:= src/minishell.c \
		   src/main_utils.c \
		   src/free_structs.c


OBJ		:= $(SRC:%.c=%.o)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS) && printf "Compiling: $(notdir $<)"

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -lreadline $(OBJ) $(HEADERS) -o $@ -Llibs/libft -lft

$(LIBFT):
	@make -C libs/libft/ --no-print-directory

clean:
	rm -rf $(OBJ)
	make -C libs/libft clean

fclean: clean
	rm -rf $(NAME)
	make -C libs/libft fclean

re:	clean all

PHONY: all, clean, fclean, re

