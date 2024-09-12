# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/07 19:31:25 by ajuliao-          #+#    #+#              #
#    Updated: 2024/09/11 21:51:47 by ajuliao-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#******************************************************************************#
#                                   PATH                                       #
#******************************************************************************#

SRC_P            := src/
LIB_P            := libs/libft/
INCS             := includes/ $(LIB_P)
CPPFLAGS         := $(addprefix -I, $(INCS)) #-MP

#******************************************************************************#
#                                  FILES                                       #
#******************************************************************************#

SRCS     += $(addprefix $(SRC_P), exec_utils.c free_structs.c main_utils.c minishell.c custom_split.c parse_utils.c put_space.c exec_tokens.c utils_exec_tokens.c tree.c heredoc.c expansion.c expansion_utils.c unset.c redirect.c pwd.c export_utils.c export.c exit.c exec.c exec_functions.c errors.c env.c echo.c cd.c utils.c list_functions_env.c signals.c signals_utils.c sig_status.c )
OBJS     += $(addprefix obj/, $(notdir $(SRCS:.c=.o)))
NAME     := minishell
LIBFT    := $(addprefix $(LIB_P), libft.a)

#******************************************************************************#
#                               BASH COMMANDS                                  #
#******************************************************************************#

RM          := rm -rf
BUILD       := obj/

#******************************************************************************#
#                                COMPILATION                                   #
#******************************************************************************#

CC       := cc
CFLAGS   :=  -g3 #-Ofast #-Wall -Wextra -Werror

#******************************************************************************#
#                                  TARGETS                                     #
#******************************************************************************#

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIB_P)

$(NAME): obj $(OBJS)
	$(CC) $(OBJS) -lreadline $(LIBFT) -o $@
	echo "Executável $@ criado com sucesso!"

obj:
	mkdir -p $(BUILD)

obj/%.o: $(SRC_P)%.c $(INCS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	make fclean -C $(LIB_P)
	$(RM) $(BUILD)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean bonus

.DEFAULT_GOAL := all

.SILENT:
