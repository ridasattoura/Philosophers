/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:42 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 10:00:00 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_forks(t_args *args, pthread_mutex_t **forks)
{
	int	i;

	*forks = malloc(sizeof(pthread_mutex_t) * args->nb_of_philo);
	if (!*forks)
		return (1);
	i = 0;
	while (i < args->nb_of_philo)
	{
		if (pthread_mutex_init(&(*forks)[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(*forks)[i]);
			free(*forks);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	cleanup_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

static int	init_philo_mutexes(t_philo *philos, t_args *args,
			pthread_mutex_t *forks)
{
	int	i;
	int	j;

	i = 0;
	while (i < args->nb_of_philo)
	{
		if (pthread_mutex_init(&philos[i].meal_mutex, NULL) != 0)
		{
			j = i;
			while (--j >= 0)
				pthread_mutex_destroy(&philos[j].meal_mutex);
			cleanup_forks(forks, args->nb_of_philo);
			free(philos);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	assign_philo_data(t_philo *philos, t_args *args,
			pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < args->nb_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].nb_eat = 0;
		philos[i].last_meal = args->start_time;
		philos[i].args = args;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % args->nb_of_philo];
		i++;
	}
}

int	init_philo(t_philo **philos, t_args *args, pthread_mutex_t **forks)
{
	if (pthread_mutex_init(&args->write_mutex, NULL) != 0)
		return (1);
	if (init_forks(args, forks))
	{
		pthread_mutex_destroy(&args->write_mutex);
		return (1);
	}
	*philos = malloc(sizeof(t_philo) * args->nb_of_philo);
	if (!*philos)
	{
		cleanup_forks(*forks, args->nb_of_philo);
		pthread_mutex_destroy(&args->write_mutex);
		return (1);
	}
	assign_philo_data(*philos, args, *forks);
	if (init_philo_mutexes(*philos, args, *forks))
	{
		pthread_mutex_destroy(&args->write_mutex);
		return (1);
	}
	return (0);
}
