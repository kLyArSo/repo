NAME = philo

FLAGS = -Wall -Wextra -Werror

SRCS = checkers.c\
		deployment_plus.c\
		error_handling.c\
		initialize.c\
		main_1.c\
		main_2.c\
		main.c\

.PHONY: all
all: $(NAME)

$(NAME):$(SRCS)
		gcc $(FLAGS) $(SRCS) -o philo

.PHONY: clean
clean:
	    rm -f $(NAME)

.PHONY: fclean
fclean: clean
	    rm -f $(NAME)

.PHONY: re
re: fclean $(NAME)