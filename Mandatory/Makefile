NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread

RM = rm -f

SRCDIR = src
INCDIR = includes
OBJDIR = obj

SOURCES = main.c \
		  init.c \
		  utils.c \
		  routine.c \
		  philo_routine.c \
		  cleanup.c \
		  args.c \
		  monitor.c

SRCS = $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
