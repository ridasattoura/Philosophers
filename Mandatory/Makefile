NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread

RM = rm -f


MANDATORY_SRCS = main.c \
		  init.c \
		  utils.c \
		  routine.c \
		  philo_routine.c \
		  cleanup.c \
		  args.c \
		  monitor.c

MANDATORY_OBJ = $(MANDATORY_SRCS:.c=.o)

HEADER_Mandatory = includes/philo.h


LIBFT = libft/libft.a
LIBFT_DIR = libft

CC = cc 
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

$(NAME): $(MANDATORY_OBJ) 
	$(CC) $(CFLAGS) $(MANDATORY_OBJ) -o $(NAME)

all: $(NAME) 

Mandatory/%.o: Mandatory/%.c $(HEADER_Mandatory)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(MANDATORY_OBJ) 

fclean: clean
	$(RM) $(NAME)


re: fclean all

.PHONY: all clean fclean re