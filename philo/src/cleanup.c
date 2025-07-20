/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:37 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 08:47:43 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clean_simulation(t_args *args, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	if (forks)
	{
		i = 0;
		while (i < args->nb_of_philo)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
		free(forks);
	}
	if (philos)
	{
		i = 0;
		while (i < args->nb_of_philo)
		{
			pthread_mutex_destroy(&philos[i].meal_mutex);
			i++;
		}
		free(philos);
	}
	pthread_mutex_destroy(&args->write_mutex);
}
