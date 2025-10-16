/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:35:55 by user              #+#    #+#             */
/*   Updated: 2025/08/03 02:35:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philosopher_eats(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	sem_wait(table->forks_sem);
	print_status(philo, TOOK_FORK);
	if (table->nb_philos == 1)
	{
		precise_sleep(table, table->time_to_die);
		print_status(philo, DIED);
		exit(1);
	}
	sem_wait(table->forks_sem);
	print_status(philo, TOOK_FORK);
	print_status(philo, IS_EATING);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	precise_sleep(table, table->time_to_eat);
	sem_post(table->forks_sem);
	sem_post(table->forks_sem);
}

void	philosopher_routine(void *arg)
{
	t_philo		*philo;
	t_table		*table;
	pthread_t	death_monitor;

	philo = (t_philo *)arg;
	table = philo->table;
	philo->last_meal_time = table->start_time;
	pthread_create(&death_monitor, NULL, monitor_death, (void *)philo);
	pthread_detach(death_monitor);
	if (philo->id % 2 == 0)
		precise_sleep(table, 10);
	while (1)
	{
		philosopher_eats(philo);
		if (table->nb_meals != -1 && philo->meals_eaten >= table->nb_meals)
			exit(0);
		print_status(philo, IS_SLEEPING);
		precise_sleep(table, table->time_to_sleep);
		print_status(philo, IS_THINKING);
	}
}
