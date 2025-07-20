/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:47 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 05:24:48 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philos)
{
	int			i;
	long long	current_time;
	long long	time_since_last_meal;

	i = 0;
	current_time = get_time_ms();
	
	while (i < philos[0].args->nb_of_philo)
	{
		time_since_last_meal = current_time - philos[i].last_meal;
		
		if (time_since_last_meal > philos[i].args->time_to_die)
		{
			pthread_mutex_lock(&philos[i].args->write_mutex);
			if (!philos[i].args->someone_dead)
			{
				philos[i].args->someone_dead = 1;
				printf("%lld %d %s\n", current_time - philos[i].args->start_time, 
					   philos[i].id, "died");
				fflush(stdout);
			}
			pthread_mutex_unlock(&philos[i].args->write_mutex);
			return (1);
		}
		i++;
	}
	
	return (0);
}

int	check_meals(t_philo *philos)
{
	int	i;
	int	all_ate_enough;

	if (philos[0].args->nb_of_eat == -1)
		return (0);
	
	all_ate_enough = 1;
	i = 0;
	while (i < philos[0].args->nb_of_philo)
	{
		if (philos[i].nb_eat < philos[i].args->nb_of_eat)
		{
			all_ate_enough = 0;
			break;
		}
		i++;
	}
	
	if (all_ate_enough)
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
	t_args	*args;

	philos = (t_philo *)philo;
	args = philos->args;
	
	ft_usleep(10);
	
	while (!check_if_dead(args))
	{
		if (check_death(philos))
			break;
		
		if (check_meals(philos))
			break;
		
		ft_usleep(1);
	}
	
	return (NULL);
}
