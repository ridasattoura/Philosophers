/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:35:38 by risattou          #+#    #+#             */
/*   Updated: 2025/08/03 02:35:39 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

enum						e_action_type
{
	TOOK_FORK = 0,
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	DIED
};

typedef struct s_philo
{
	int						id;
	int						meals_eaten;
	long					last_meal_time;
	struct s_philo			*next;
	struct s_philo			*prev;
	struct s_table			*table;
	pid_t					process_id;
}							t_philo;

typedef struct s_table
{
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						nb_meals;
	int						nb_philos;
	long					start_time;
	t_philo					*philos;
	sem_t					*print_sem;
	sem_t					*forks_sem;
	sem_t					*death_sem;
}							t_table;

int							ft_isdigit(int c);
size_t						ft_strlen(const char *s);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
int							ft_atoi(const char *str);
int							validate_args(int argc, char *argv[],
								t_table *table);
void						print_status(t_philo *philo, int action);
void						philosopher_routine(void *arg);
void						cleanup_and_exit(t_table *table);
long						get_current_time(void);
void						precise_sleep(t_table *table, long time_ms);
void						*monitor_death(void *arg);

#endif
