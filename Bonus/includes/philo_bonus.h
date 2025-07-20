/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:23:52 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 08:18:17 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_args	t_args;

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	long long		last_meal;
	pid_t			pid;
	t_args			*args;
}	t_philo;

typedef struct s_args
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_eat;
	int				someone_dead;
	int				finished_count;
	long long		start_time;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*meal_sem;
	sem_t			*stop_sem;
	sem_t			*finished_sem;
	pthread_mutex_t	pids_mutex;
	t_philo			*philos;
	pid_t			*pids;
}	t_args;

int			main(int argc, char **argv);
int			parse_arguments(int argc, char **argv, t_args *args);
int			is_valid_number(const char *str);
void		kill_all_processes(t_args *args);
int			wait_for_processes(t_args *args);

int			init_data(t_args *args);
int			init_philos(t_args *args);
int			init_semaphores(t_args *args);

long long	get_time_ms(void);
void		ft_usleep(int time);
void		print_status(t_philo *philo, char *status);
int			ft_atoi(const char *str);
int			check_if_dead(t_args *args);

void		philosopher_process(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		*death_monitor(void *arg);
void		single_philosopher_process(t_philo *philo);

void		*monitor_routine(void *arg);
int			check_death(t_args *args);
int			check_meals_completion(t_args *args);

void		cleanup_data(t_args *args);
void		destroy_semaphores(t_args *args);
void		unlink_semaphores(void);

#endif
