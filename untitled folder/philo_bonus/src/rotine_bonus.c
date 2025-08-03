/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:36:01 by risattou          #+#    #+#             */
/*   Updated: 2025/08/03 02:36:02 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	philosopher_eats(t_philosopher *philo)
{
	t_dining_table	*table;

	table = philo->table;
	sem_wait(philo->table->fork_sem);
	print_status(philo, TOOK_FORK);
	if (philo->table->philo_count == 1)
	{
		precise_sleep(table, table->time_to_die);
		print_status(philo, DIED);
		table->someone_died = 1;
		return ;
	}
	sem_wait(philo->table->fork_sem);
	print_status(philo, TOOK_FORK);
	sem_wait(philo->table->check_sem);
	philo->meals_eaten++;
	print_status(philo, IS_EATING);
	philo->last_meal_time = get_current_time();
	sem_post(philo->table->check_sem);
	precise_sleep(table, table->time_to_eat);
	sem_post(philo->table->fork_sem);
	sem_post(philo->table->fork_sem);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_dining_table	*table;

	philo = (t_philosopher *)arg;
	table = philo->table;
	philo->last_meal_time = table->start_time;
	pthread_create(&philo->death_monitor, NULL, monitor_death, (void *)philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!table->someone_died)
	{
		philosopher_eats(philo);
		if (table->max_meals != -1 && philo->meals_eaten >= table->max_meals)
			break ;
		print_status(philo, IS_SLEEPING);
		precise_sleep(table, table->time_to_sleep);
		print_status(philo, IS_THINKING);
	}
	pthread_join(philo->death_monitor, NULL);
	exit (0);
}
