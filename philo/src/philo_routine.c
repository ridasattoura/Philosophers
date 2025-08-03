/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:00:00 by ader              #+#    #+#             */
/*   Updated: 2025/07/29 11:03:11 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	calculate_think_time(t_philo *ph)
{
	int	base_time;
	int	adaptive_time;
	
	if (ph->args->nb_of_philo % 2 == 1)
		base_time = ph->args->time_to_eat / 2;
	else
		base_time = 0;
	
	// Add adaptive thinking time based on philosopher count
	if (ph->args->nb_of_philo > 5)
	{
		adaptive_time = (ph->args->time_to_eat * ph->args->nb_of_philo) / 20;
		return (base_time + adaptive_time);
	}
	return (base_time);
}

void	*start_routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (ph->id % 2 == 0)
		ft_usleep(calculate_think_time(ph));
	while (!check_if_dead(ph->args))
	{
		print_status(ph, "is thinking");
		if (ph->args->nb_of_philo % 2 == 1)
			ft_usleep(1);
		eat_and_sleep(ph);
		if (ph->args->nb_of_eat != -1 && ph->nb_eat >= ph->args->nb_of_eat)
			break ;
	}
	return (NULL);
}
