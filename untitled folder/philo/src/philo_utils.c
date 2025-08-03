/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:27:24 by risattou          #+#    #+#             */
/*   Updated: 2025/08/03 02:43:57 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	samone_died(t_dining_table *table, int i)
{
	print_status(&table->philosophers[i], DIED);
	table->someone_died = 1;
}

void	monitor_philosophers(t_dining_table *table)
{
	int	i;

	while (!table->all_satisfied)
	{
		i = -1;
		while (!table->someone_died && ++i < table->philo_count)
		{
			pthread_mutex_lock(&table->check_mutex);
			if (get_current_time() - table->philosophers[i].last_meal_time 
				> (size_t)table->time_to_die)
				samone_died(table, i);
			pthread_mutex_unlock(&table->check_mutex);
			usleep(100);
		}
		if (table->someone_died)
			break ;
		i = 0;
		while (table->max_meals != -1 && i < table->philo_count
			&& table->philosophers[i].meals_eaten >= table->max_meals)
			i++;
		if (i == table->philo_count)
			table->all_satisfied = 1;
	}
}

void	cleanup_and_exit(t_dining_table *table, pthread_t *thread_ids)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
		pthread_join(thread_ids[i], NULL);
	i = -1;
	while (++i < table->philo_count)
		pthread_mutex_destroy(&table->philosophers[i].fork);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->check_mutex);
	free(table->philosophers);
	free(thread_ids);
}

size_t	get_current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	precise_sleep(t_dining_table *table, size_t duration)
{
	size_t	start_time;

	start_time = get_current_time();
	while (!(table->someone_died))
	{
		if (get_current_time() - start_time >= duration)
			break ;
		usleep(100);
	}
}
