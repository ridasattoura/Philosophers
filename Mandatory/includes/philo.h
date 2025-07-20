/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:29 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 05:24:30 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_args
{
    int				nb_of_philo;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				nb_of_eat;
    int				someone_dead;
    long long		start_time;
    pthread_mutex_t	write_mutex;
    pthread_t		monitoring_thread;
}	t_args;

typedef struct s_philo
{
    int				id;
    int				nb_eat;
    long long		last_meal;
    pthread_mutex_t	*left_fork;
    pthread_mutex_t	*right_fork;
    pthread_t		thread;
    t_args			*args;
}	t_philo;

int			parse_arguments(int argc, char **argv, t_args *args);
int			init_philo(t_philo **philos, t_args *args, pthread_mutex_t **forks);
void		clean_simulation(t_args *args, t_philo *philos, pthread_mutex_t *forks);
void		*start_routine(void *philo);
void		*monitoring(void *philo);
void		eat_and_sleep(t_philo *philo);
long long	get_time_ms(void);
void		ft_usleep(int time);
void		print_status(t_philo *philo, char *status);
int			ft_atoi(const char *str);
int			check_if_dead(t_args *args);
int			check_args(int ac, char **av);
int			is_valid_number(const char *str);

#endif
