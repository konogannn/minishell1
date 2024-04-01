##
## EPITECH PROJECT, 2023
## minishell1
## File description:
## Makefile
##

CC	=	gcc

TARGET	=	mysh

UNIT_TESTS	=	unit_tests

CFLAGS	=	-Wall -Wextra -Wshadow -I./include

LDFLAGS = -L. -lmy

CRITERIONFLAGS	=	--coverage -lcriterion

SRC	=	src/main.c				\
		src/builtin.c			\
		src/cmd.c				\
		src/minishell.c			\
		src/builtin/cd.c		\
		src/builtin/env.c		\
		src/builtin/exit.c		\
		src/builtin/setenv.c	\
		src/builtin/unsetenv.c	\
		src/parsing/format.c	\
		src/parsing/parse_cmd.c

SRCTEST	=	$(filter-out src/main.c, $(SRC))

FILETEST	=	tests/test_libc.c		\
				tests/test_minishell1.c

OBJ	=	$(SRC:.c=.o)

.PHONY: all clean fclean re tests_run

all: $(TARGET)

$(TARGET):	$(OBJ)
	@echo -e "\e[1m\e[36mBuilding $(TARGET)...\e[0m"
	@$(MAKE) -C ./lib/my -lmy > /dev/null 2>&1
	@$(CC) -o $(TARGET) $(OBJ) $(CFLAGS) $(LDFLAGS)
	@echo -e "\e[1m\e[32mBinary ready!\e[0m"

$(UNIT_TESTS):	fclean
	@$(MAKE) -C ./lib/my > /dev/null 2>&1
	@$(CC) -o $(UNIT_TESTS) $(SRCTEST) $(FILETEST) $(LDFLAGS) \
	$(CRITERIONFLAGS)

tests_run:	$(UNIT_TESTS)
	@./$(UNIT_TESTS)
	@gcovr --exclude tests/

clean:
	@$(MAKE) clean -C ./lib/my > /dev/null 2>&1
	@rm -f $(OBJ)
	@rm -f *.gc*
	@rm -f coding-style-reports.log

fclean: clean
	@$(MAKE) fclean -C ./lib/my > /dev/null 2>&1
	@rm -f $(TARGET)
	@rm -f $(UNIT_TESTS)

re: fclean all
