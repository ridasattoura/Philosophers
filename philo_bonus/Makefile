NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread
RM = rm -f

SRCDIR = src_bonus
INCDIR = includes_bonus

BONUS_SRCS = main_bonus.c init_bonus.c semaphore_bonus.c status_bonus.c utils_bonus.c \
		  args_bonus.c process_bonus.c process_routine_bonus.c process_monitor_bonus.c \
		  monitor_bonus.c cleanup_bonus.c

BONUS_OBJ = $(addprefix $(SRCDIR)/, $(BONUS_SRCS:.c=.o))

HEADER_BONUS = includes_bonus/philo_bonus.h

$(NAME): $(BONUS_OBJ) 
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(NAME)

all: $(NAME) 

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(HEADER_BONUS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	$(RM) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re