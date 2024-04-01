##
## EPITECH PROJECT, 2023
## libc
## File description:
## Makefile
##

CC	=	gcc

NAME	=	libmy.a

SRC	=	mini_printf.c			\
		my_put_nbr.c			\
		my_putchar.c			\
		my_putstr.c				\
		my_strcat.c				\
		my_strcmp.c				\
		my_strdup.c				\
		my_strlen.c				\
		my_strncmp.c			\
		dup_env.c	\
		list.c		\
		manage.c

OBJ	=	$(SRC:.c=.o)

.PHONY: all clean fclean re

all:	$(NAME)

$(NAME):	$(OBJ)
	@ar rc $(NAME) $(OBJ)
	@mv $(NAME) ../../$(NAME)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f ../../$(NAME)

re:	fclean all
