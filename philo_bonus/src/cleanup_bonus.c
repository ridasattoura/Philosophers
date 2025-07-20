/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:02 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 12:21:21 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	unlink_semaphores(void)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_meal");
	sem_unlink("/philo_stop");
	sem_unlink("/philo_finished");
}

void	destroy_semaphores(t_args *args)
{
	if (args->forks && args->forks != SEM_FAILED)
		sem_close(args->forks);
	if (args->print_sem && args->print_sem != SEM_FAILED)
		sem_close(args->print_sem);
	if (args->meal_sem && args->meal_sem != SEM_FAILED)
		sem_close(args->meal_sem);
	if (args->stop_sem && args->stop_sem != SEM_FAILED)
		sem_close(args->stop_sem);
	if (args->finished_sem && args->finished_sem != SEM_FAILED)
		sem_close(args->finished_sem);
	unlink_semaphores();
}

void	cleanup_data(t_args *args)
{
	destroy_semaphores(args);
	pthread_mutex_destroy(&args->pids_mutex);
	if (args->philos)
	{
		free(args->philos);
		args->philos = NULL;
	}
	if (args->pids)
	{
		free(args->pids);
		args->pids = NULL;
	}
}
