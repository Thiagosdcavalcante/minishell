NAME = libft.a

FILES = ft_bzero.c\
 ft_isalnum.c\
 ft_isalpha.c\
 ft_isascii.c\
 ft_isdigit.c\
 ft_isprint.c\
 ft_memchr.c\
 ft_memcmp.c\
 ft_memcpy.c\
 ft_memmove.c\
 ft_memset.c\
 ft_strchr.c\
 ft_strlen.c\
 ft_strncmp.c\
 ft_strrchr.c\
 ft_tolower.c\
 ft_toupper.c\
 ft_strnstr.c\
 ft_atoi.c\
 ft_strdup.c\
 ft_calloc.c\
 ft_strlcpy.c\
 ft_strlcat.c\
 ft_substr.c\
 ft_strjoin.c\
 ft_strtrim.c\
 ft_split.c\
 ft_itoa.c\
 ft_strmapi.c\
 ft_striteri.c\
 ft_putchar_fd.c\
 ft_putstr_fd.c\
 ft_putendl_fd.c\
 ft_putnbr_fd.c\
 ft_itoa_u.c\
 ft_printf_utils.c\
 ft_printf.c\
 get_next_line_utils.c\
 get_next_line.c

B_FILES = ft_lstnew.c\
 ft_lstadd_front.c\
 ft_lstsize.c\
 ft_lstlast.c\
 ft_lstadd_back.c\
 ft_lstdelone.c\
 ft_lstiter.c\
 ft_lstclear.c

COMPILER = cc
FLAGS = -Wall -Wextra -Werror

OBS = $(FILES:%.c=%.o)
OBS_B = $(B_FILES:%.c=%.o)

WITH_BONUS=TRUE

ifdef	WITH_BONUS
	OBS += $(OBS_B)
endif

all: $(NAME)

$(NAME): $(OBS)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBS) $(OBS_B)

re: fclean $(NAME)

%.o: %.c
	@echo "Compiling $@"
	@$(COMPILER) $(FLAGS) -c $< -o $@ -I ./
	@ar rc $(NAME) $@

.PHONY: all clean fclean re
