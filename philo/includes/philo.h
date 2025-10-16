/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:26:10 by risattou          #+#    #+#             */
/*   Updated: 2025/08/03 02:26:12 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

enum						e_action_type
{
	TOOK_FORK = 0,
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	DIED
};

typedef struct s_philosopher
{
	int						id;
	int						meals_eaten;
	size_t					last_meal_time;
	pthread_mutex_t			fork;
	struct s_philosopher	*next;
	struct s_philosopher	*prev;
	struct s_dining_table	*table;
}							t_philosopher;

typedef struct s_dining_table
{
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						max_meals;
	int						philo_count;
	int						all_satisfied;
	int						someone_died;
	size_t					start_time;
	t_philosopher			*philosophers;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			check_mutex;
}							t_dining_table;

int							ft_isdigit(int c);
size_t						ft_strlen(const char *s);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
int							ft_atoi(const char *str);
int							validate_arguments(int argc, char *argv[],
								t_dining_table *table);
void						print_status(t_philosopher *philo, int action);
void						*philosopher_routine(void *arg);
void						monitor_philosophers(t_dining_table *table);
void						cleanup_and_exit(t_dining_table *table,
								pthread_t *thread_ids);
size_t						get_current_time(void);
void						precise_sleep(t_dining_table *table,
								size_t duration);

#endif
