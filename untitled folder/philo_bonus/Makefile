NAME = philo_bonus

SRCS = src/main.c src/valider_args.c src/utils.c src/put_mssg.c \
		src/rotine.c src/philo_utils.c

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
