/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:42 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 05:24:43 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_philo(t_philo **philos, t_args *args, pthread_mutex_t **forks)
{
	int	i;

	if (pthread_mutex_init(&args->write_mutex, NULL) != 0)
		return (1);

	*forks = malloc(sizeof(pthread_mutex_t) * args->nb_of_philo);
	if (!*forks)
	{
		pthread_mutex_destroy(&args->write_mutex);
		return (1);
	}

	i = 0;
	while (i < args->nb_of_philo)
	{
		if (pthread_mutex_init(&(*forks)[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(*forks)[i]);
			free(*forks);
			pthread_mutex_destroy(&args->write_mutex);
			return (1);
		}
		i++;
	}

	*philos = malloc(sizeof(t_philo) * args->nb_of_philo);
	if (!*philos)
	{
		i = 0;
		while (i < args->nb_of_philo)
		{
			pthread_mutex_destroy(&(*forks)[i]);
			i++;
		}
		free(*forks);
		pthread_mutex_destroy(&args->write_mutex);
		return (1);
	}

	i = 0;
	while (i < args->nb_of_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].nb_eat = 0;
		(*philos)[i].last_meal = args->start_time;
		(*philos)[i].args = args;
		(*philos)[i].left_fork = &(*forks)[i];
		(*philos)[i].right_fork = &(*forks)[(i + 1) % args->nb_of_philo];
		i++;
	}

	return (0);
}
