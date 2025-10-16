/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:35:55 by user              #+#    #+#             */
/*   Updated: 2025/08/03 02:35:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	precise_sleep(t_table *table, long time_ms)
{
	long	start_time;

	(void)table;
	start_time = get_current_time();
	while (get_current_time() - start_time < time_ms)
		usleep(100);
}

void	cleanup_and_exit(t_table *table)
{
	sem_close(table->print_sem);
	sem_close(table->forks_sem);
	sem_close(table->death_sem);
	sem_unlink("/sem_print");
	sem_unlink("/sem_forks");
	sem_unlink("/sem_death");
	free(table->philos);
	exit(0);
}

void	*monitor_death(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (1)
	{
		usleep(1000);
		if (get_current_time() - philo->last_meal_time > table->time_to_die)
		{
			print_status(philo, DIED);
			sem_post(table->death_sem);
			exit(1);
		}
	}
	return (NULL);
}
