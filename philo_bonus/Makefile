NAME = philo_bonus

SRCS = src/main_bonus.c src/validate_args_bonus_bonus.c src/utils_bonus.c src/put_mssg_bonus.c \
		src/rotine_bonus.c src/philo_utils_bonus.c

SRCOB = $(SRCS:.c=.o)
HEADER = includes/philo_bonus.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

$(NAME): $(SRCOB)
	$(CC) $(CFLAGS) $(SRCOB) -o $(NAME)

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	$(RM) $(SRCOB)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
