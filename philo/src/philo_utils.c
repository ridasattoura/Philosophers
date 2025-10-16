/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:27:24 by risattou          #+#    #+#             */
/*   Updated: 2025/08/03 07:03:27 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	samone_died(t_dining_table *table, int i)
{
	print_status(&table->philosophers[i], DIED);
	pthread_mutex_lock(&table->check_mutex);
	table->someone_died = 1;
	pthread_mutex_unlock(&table->check_mutex);
}

void	check_philosopher_death(t_dining_table *table, int i, int *dead)
{
	pthread_mutex_lock(&table->check_mutex);
	if (get_current_time() - table->philosophers[i].last_meal_time 
		> (size_t)table->time_to_die)
	{
		if (!table->someone_died)
		{
			table->someone_died = 1;
			*dead = 1;
			pthread_mutex_unlock(&table->check_mutex);
			print_status(&table->philosophers[i], DIED);
		}
		else
		{
			*dead = table->someone_died;
			pthread_mutex_unlock(&table->check_mutex);
		}
	}
	else
	{
		*dead = table->someone_died;
		pthread_mutex_unlock(&table->check_mutex);
	}
	usleep(100);
}

int	check_all_satisfied(t_dining_table *table)
{
	int	i;
	int	satisfied;

	satisfied = 0;
	i = 0;
	pthread_mutex_lock(&table->check_mutex);
	while (table->max_meals != -1 && i < table->philo_count
		&& table->philosophers[i].meals_eaten >= table->max_meals)
		i++;
	if (i == table->philo_count && table->max_meals != -1)
	{
		table->all_satisfied = 1;
		satisfied = table->all_satisfied;
	}
	else
		satisfied = table->all_satisfied;
	pthread_mutex_unlock(&table->check_mutex);
	return (satisfied);
}

void	monitor_philosophers(t_dining_table *table)
{
	int	i;
	int	dead;
	int	satisfied;

	while (1)
	{
		i = -1;
		pthread_mutex_lock(&table->check_mutex);
		dead = table->someone_died;
		pthread_mutex_unlock(&table->check_mutex);
		while (!dead && ++i < table->philo_count)
			check_philosopher_death(table, i, &dead);
		if (dead)
			break ;
		satisfied = check_all_satisfied(table);
		if (satisfied)
			break ;
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
