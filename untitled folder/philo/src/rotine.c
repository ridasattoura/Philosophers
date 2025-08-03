/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:27:30 by risattou          #+#    #+#             */
/*   Updated: 2025/08/03 06:07:55 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philosopher_eats(t_philosopher *philo)
{
	t_dining_table	*table;

	table = philo->table;
	pthread_mutex_lock(&philo->fork);
	print_status(philo, TOOK_FORK);
	if (philo->table->philo_count == 1)
	{
		precise_sleep(table, table->time_to_die);
		print_status(philo, DIED);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_lock(&table->check_mutex);
		table->someone_died = 1;
		pthread_mutex_unlock(&table->check_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->next->fork);
	print_status(philo, TOOK_FORK);
	pthread_mutex_lock(&table->check_mutex);
	philo->meals_eaten++;
	print_status(philo, IS_EATING);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&table->check_mutex);
	precise_sleep(table, table->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_dining_table	*table;
	int				dead;
	int				satisfied;

	philo = (t_philosopher *)arg;
	table = philo->table;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&table->check_mutex);
		dead = table->someone_died;
		satisfied = table->all_satisfied;
		pthread_mutex_unlock(&table->check_mutex);
		if (dead || satisfied)
			break ;
		philosopher_eats(philo);
		print_status(philo, IS_SLEEPING);
		precise_sleep(table, table->time_to_sleep);
		print_status(philo, IS_THINKING);
	}
	return (NULL);
}
