/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 08:30:00 by ader              #+#    #+#             */
/*   Updated: 2025/07/20 12:55:19 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	init_basic_semaphores(t_args *args)
{
	args->forks = sem_open("/philo_forks", O_CREAT | O_EXCL, 0644,
			args->nb_of_philo);
	if (args->forks == SEM_FAILED)
	{
		printf("Error: Failed to create forks semaphore\n");
		return (1);
	}
	args->print_sem = sem_open("/philo_print", O_CREAT | O_EXCL, 0644, 1);
	if (args->print_sem == SEM_FAILED)
	{
		printf("Error: Failed to create print semaphore\n");
		sem_close(args->forks);
		sem_unlink("/philo_forks");
		return (1);
	}
	return (0);
}

static int	init_control_semaphores(t_args *args)
{
	args->meal_sem = sem_open("/philo_meal", O_CREAT | O_EXCL, 0644, 1);
	if (args->meal_sem == SEM_FAILED)
	{
		printf("Error: Failed to create meal semaphore\n");
		return (1);
	}
	args->stop_sem = sem_open("/philo_stop", O_CREAT | O_EXCL, 0644, 1);
	if (args->stop_sem == SEM_FAILED)
	{
		printf("Error: Failed to create stop semaphore\n");
		sem_close(args->meal_sem);
		sem_unlink("/philo_meal");
		return (1);
	}
	args->finished_sem = sem_open("/philo_finished", O_CREAT | O_EXCL, 0644, 1);
	if (args->finished_sem == SEM_FAILED)
	{
		printf("Error: Failed to create finished semaphore\n");
		sem_close(args->meal_sem);
		sem_close(args->stop_sem);
		sem_unlink("/philo_meal");
		sem_unlink("/philo_stop");
		return (1);
	}
	return (0);
}

int	init_semaphores(t_args *args)
{
	if (init_basic_semaphores(args))
		return (1);
	if (init_control_semaphores(args))
	{
		sem_close(args->forks);
		sem_close(args->print_sem);
		sem_unlink("/philo_forks");
		sem_unlink("/philo_print");
		return (1);
	}
	return (0);
}
