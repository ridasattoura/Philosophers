NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread
RM = rm -f

SRCDIR = src
INCDIR = includes

MANDATORY_SRCS = main.c \
		  init.c \
		  utils.c \
		  routine.c \
		  philo_routine.c \
		  cleanup.c \
		  args.c \
		  monitor.c

MANDATORY_OBJ = $(addprefix $(SRCDIR)/, $(MANDATORY_SRCS:.c=.o))

HEADER_Mandatory = includes/philo.h

$(NAME): $(MANDATORY_OBJ) 
	$(CC) $(CFLAGS) $(MANDATORY_OBJ) -o $(NAME)

all: $(NAME) 

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(HEADER_Mandatory)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	$(RM) $(MANDATORY_OBJ) 

fclean: clean
	$(RM) $(NAME)


re: fclean all

.PHONY: all clean fclean re