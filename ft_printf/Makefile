.PHONY: all clean fclean re

NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS := ft_printf.c print_hex.c print_pointer.c print_unsigned_number.c print_char.c print_number.c print_string.c\
		ft_putchar_fd.c ft_putstr_fd.c ft_strlen.c

OBJS := $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -fv $(NAME) 

re: fclean all