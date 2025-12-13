.PHONY: all fclean clean re

NAME=pipex
CC=cc
CFLAGS=-Wall -Wextra -Werror -g 

LIBFT_MAKE=make -C Libft
LIBFT_LIB=Libft/libft.a

SRC:=pipex.c error_handler.c
OBJ:=$(SRC:%.c=%.o)	

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME)

$(LIBFT_LIB):
	$(LIBFT_MAKE) all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJ)
	$(LIBFT_MAKE) clean

fclean: clean 
	rm -f $(NAME)
	$(LIBFT_MAKE) fclean

re: fclean all 
