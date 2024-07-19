# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erpiana <erpiana@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/08 20:31:12 by erpiana           #+#    #+#              #
#    Updated: 2024/07/09 17:18:22 by tsantana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#******************************************************************************#
#                                   PATH                                       #
#******************************************************************************#

SRC_P            := src/
LIB_P            := libs/libft/
INCS             := includes/ $(LIB_P)
CPPFLAGS         := $(addprefix -I, $(INCS)) -MP

#******************************************************************************#
#                                  FILES                                       #
#******************************************************************************#

SRCS     += $(addprefix $(SRC_P), free_structs.c main_utils.c minishell.c \
			custom_split.c parse_utils.c put_space.c env_vars.c export_var.c \
			checks.c exec_functions.c tree.c lst_tokens.c)

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
CFLAGS   :=  -g3 -Ofast -Wall -Wextra -Werror

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
