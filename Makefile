.PHONY: all fclean clean re

NAME=pipex
CC=cc
CFLAGS=-Wall -Wextra -Werror -g 

PRINTF_MAKE=make -C ft_printf
PRINTF_EXEC=ft_printf/libftprintf.a

SRC:=pipex.c error_handler.c
OBJ:=$(SRC:%.c=%.o)	

all: $(NAME)

$(NAME): $(PRINTF_EXEC) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(PRINTF_EXEC) -o $(NAME)

$(PRINTF_EXEC):
	$(PRINTF_MAKE) all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJ)
	$(PRINTF_MAKE) clean

fclean: clean 
	rm -f $(NAME)
	$(PRINTF_MAKE) fclean

re: fclean all 
