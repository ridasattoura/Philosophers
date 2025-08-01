/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_routine_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 08:00:00 by ader              #+#    #+#             */
/*   Updated: 2025/07/23 15:12:15 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->args->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	int	think_time;

	print_status(philo, "is thinking");
	if (philo->args->nb_of_philo % 2 == 1 && philo->args->nb_of_philo > 3)
	{
		think_time = philo->args->time_to_eat / 2;
		if (think_time > 0)
			ft_usleep(think_time);
	}
}

void	*death_monitor(void *arg)
{
	t_philo		*philo;
	long long	current_time;
	long long	time_since_last_meal;

	philo = (t_philo *)arg;
	while (!check_if_dead(philo->args))
	{
		current_time = get_time_ms();
		sem_wait(philo->args->meal_sem);
		time_since_last_meal = current_time - philo->last_meal;
		sem_post(philo->args->meal_sem);
		if (time_since_last_meal > philo->args->time_to_die)
		{
			sem_wait(philo->args->print_sem);
			printf("%lld %d died\n", current_time - philo->args->start_time,
				philo->id);
			exit(1);
		}
		ft_usleep(1);
	}
	return (NULL);
}

void	single_philosopher_process(t_philo *philo)
{
	philo->last_meal = get_time_ms();
	print_status(philo, "is thinking");
	ft_usleep(philo->args->time_to_die + 1);
	print_status(philo, "died");
	exit(1);
}
