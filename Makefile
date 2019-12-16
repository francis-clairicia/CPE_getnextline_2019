##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

MAIN		=	main.c

SRC_DIR		=	.

#SRC_NO_TEST	=	$(SRC_DIR)/

SRC_TEST	=	$(SRC_DIR)/get_next_line.c

SRC			=	$(SRC_NO_TEST) $(SRC_TEST)

CFLAGS		=	-I./ -Wall -Wextra

OBJ			=	$(MAIN:.c=.o) $(SRC:.c=.o)

NAME		=	get_next_line

all:	debug

tests_run:
	@find . -name "*.gc*" -delete
	gcc -o unit_tests $(SRC_TEST) tests/*.c $(LIB) $(CFLAGS) --coverage -lcriterion
	./unit_tests
	rm -f unit_tests test*.gc*
	mkdir -p coverage
	mv *.gc* coverage/

debug:	lib
	gcc -g -o $(NAME) $(MAIN) $(SRC) $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -f unit_tests *.gc*

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all lib tests_run debug clean fclean re
