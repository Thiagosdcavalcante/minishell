# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/12 14:23:04 by tsantana          #+#    #+#              #
#    Updated: 2024/04/23 20:12:22 by tsantana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#MAKEFILE TEST#

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
	ft_strlen.c ft_strncmp.c ft_strrchr.c ft_toupper.c \
	ft_tolower.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c \
	ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_lstadd_front_bonus.c \
	ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c \
	ft_lstiter_bonus.c ft_printf.c ft_printf_utils.c ft_printf_utils_2.c \

HEADER = -I./libft.h

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@
	
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re bonus
