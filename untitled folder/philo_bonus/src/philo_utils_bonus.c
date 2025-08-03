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

	start_time = get_current_time();
	while (!table->someone_died)
	{
		if (get_current_time() - start_time >= time_ms)
			break ;
		usleep(100);
	}
}

int	monitor_death(t_table *table)
{
	int		ret;

	sem_wait(table->check_sem);
	ret = table->someone_died;
	sem_post(table->check_sem);
	return (ret);
}

void	cleanup_and_exit(t_table *table)
{
	sem_close(table->print_sem);
	sem_close(table->check_sem);
	sem_close(table->forks_sem);
	sem_unlink("/sem_print");
	sem_unlink("/sem_check");
	sem_unlink("/sem_forks");
	free(table->philos);
	exit(0);
}
