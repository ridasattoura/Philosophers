NAME = philo_bonus

SRCS = src_bonus/main_bonus.c src_bonus/init_bonus.c src_bonus/semaphore_bonus.c \
		src_bonus/status_bonus.c src_bonus/utils_bonus.c src_bonus/args_bonus.c \
		src_bonus/process_bonus.c src_bonus/process_routine_bonus.c \
		src_bonus/monitor_bonus.c src_bonus/cleanup_bonus.c

SRCOB = $(SRCS:.c=.o)
HEADER = includes_bonus/philo_bonus.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

$(NAME): $(SRCOB)
	$(CC) $(CFLAGS) $(SRCOB) -o $(NAME)

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -Iincludes_bonus -c $< -o $@

clean:
	$(RM) $(SRCOB)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re