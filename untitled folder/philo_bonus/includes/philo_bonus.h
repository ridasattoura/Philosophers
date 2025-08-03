#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>


enum e_action_type {
	TOOK_FORK = 0,
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	DIED
};

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	size_t			last_meal_time;
	struct s_philosopher	*next;
	struct s_philosopher	*prev;
	struct s_dining_table	*table;
	pid_t			process_id;
	pthread_t		death_monitor;
}	t_philosopher;

typedef struct s_dining_table
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				philo_count;
	int				all_satisfied;
	int				someone_died;
	size_t			start_time;
	t_philosopher		*philosophers;
	sem_t			*print_sem;
	sem_t			*check_sem;
	sem_t			*fork_sem;
}	t_dining_table;

int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		validate_arguments(int argc, char *argv[], t_dining_table *table);
void	print_status(t_philosopher *philo, int action);
void	*philosopher_routine(void *arg);
void	cleanup_and_exit(t_dining_table *table);
size_t	get_current_time(void);
void	precise_sleep(t_dining_table *table, size_t duration);
void	*monitor_death(void *arg);

#endif
