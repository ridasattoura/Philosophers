/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:47 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 13:10:14 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	announce_death(t_philo *philo, long long current_time)
{
	pthread_mutex_lock(&philo->args->write_mutex);
	if (!philo->args->someone_dead)
	{
		philo->args->someone_dead = 1;
		printf("%lld %d died\n", current_time - philo->args->start_time,
			philo->id);
		fflush(stdout);
	}
	pthread_mutex_unlock(&philo->args->write_mutex);
}

int	check_death(t_philo *philos)
{
	int			i;
	long long	current_time;
	long long	time_since_last_meal;

	i = 0;
	current_time = get_time_ms();
	while (i < philos[0].args->nb_of_philo)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		time_since_last_meal = current_time - philos[i].last_meal;
		pthread_mutex_unlock(&philos[i].meal_mutex);
		if (time_since_last_meal > philos[i].args->time_to_die)
		{
			announce_death(&philos[i], current_time);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_all_meals(t_philo *philos)
{
	int	i;
	int	current_nb_eat;

	i = 0;
	while (i < philos[0].args->nb_of_philo)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		current_nb_eat = philos[i].nb_eat;
		pthread_mutex_unlock(&philos[i].meal_mutex);
		if (current_nb_eat < philos[i].args->nb_of_eat)
			return (0);
		i++;
	}
	return (1);
}

int	check_meals(t_philo *philos)
{
	if (philos[0].args->nb_of_eat == -1)
		return (0);
	if (check_all_meals(philos))
	{
		pthread_mutex_lock(&philos[0].args->write_mutex);
		philos[0].args->someone_dead = 1;
		pthread_mutex_unlock(&philos[0].args->write_mutex);
		return (1);
	}
	return (0);
}

void	*monitoring(void *philo)
{
	t_philo	*philos;

	philos = (t_philo *)philo;
	ft_usleep(10);
	while (!check_if_dead(philos->args))
	{
		if (check_death(philos))
			break ;
		if (check_meals(philos))
			break ;
		ft_usleep(1);
	}
	return (NULL);
}
