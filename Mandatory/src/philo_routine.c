/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:00:00 by ader              #+#    #+#             */
/*   Updated: 2025/07/20 08:47:43 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	calculate_think_time(t_philo *ph)
{
	int	cycle_time;
	int	max_safe_think;
	int	safe_think_time;

	cycle_time = ph->args->time_to_eat + ph->args->time_to_sleep;
	safe_think_time = 0;
	if (ph->args->nb_of_philo % 2 == 1 && ph->args->nb_of_philo > 3)
	{
		max_safe_think = ph->args->time_to_die - cycle_time - 50;
		if (max_safe_think > 0)
		{
			safe_think_time = ph->args->time_to_eat / 2;
			if (safe_think_time > max_safe_think)
				safe_think_time = max_safe_think;
		}
	}
	return (safe_think_time);
}

void	*start_routine(void *philo)
{
	t_philo	*ph;
	int		think_time;

	ph = (t_philo *)philo;
	if (ph->id % 2 == 0)
		ft_usleep(ph->args->time_to_eat / 2);
	while (!check_if_dead(ph->args))
	{
		print_status(ph, "is thinking");
		think_time = calculate_think_time(ph);
		if (think_time > 0)
			ft_usleep(think_time);
		eat_and_sleep(ph);
		if (ph->args->nb_of_eat != -1 && ph->nb_eat >= ph->args->nb_of_eat)
			break ;
	}
	return (NULL);
}
