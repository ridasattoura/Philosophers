NAME = philo_bonus


CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread
RM = rm -f

SRCDIR = src
INCDIR = includes
OBJDIR = obj

SOURCES = main_bonus.c \
		  init_bonus.c \
		  semaphore_bonus.c \
		  status_bonus.c \
		  utils_bonus.c \
		  args_bonus.c \
		  process_bonus.c \
		  process_routine_bonus.c \
		  process_monitor_bonus.c \
		  monitor_bonus.c \
		  cleanup_bonus.c

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
