/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:08 by risattou          #+#    #+#             */
/*   Updated: 2025/07/29 10:49:35 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

static int	allocate_philo_arrays(t_args *args)
{
	args->philos = malloc(sizeof(t_philo) * args->nb_of_philo);
	if (!args->philos)
		return (1);
	args->pids = malloc(sizeof(pid_t) * args->nb_of_philo);
	if (!args->pids)
	{
		free(args->philos);
		args->philos = NULL;
		return (1);
	}
	return (0);
}

static void	initialize_philosopher_data(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_of_philo)
	{
		args->philos[i].id = i + 1;
		args->philos[i].nb_eat = 0;
		args->philos[i].last_meal = 0;
		args->philos[i].args = args;
		args->pids[i] = 0;
		i++;
	}
}

int	init_philos(t_args *args)
{
	if (allocate_philo_arrays(args))
		return (1);
	initialize_philosopher_data(args);
	return (0);
}

static int	init_data_components(t_args *args)
{
	args->pids_sem = sem_open("/philo_pids_sem", O_CREAT | O_EXCL, 0644, 1);
	if (args->pids_sem == SEM_FAILED)
	{
		printf("Error: Failed to initialize PIDs semaphore\n");
		return (1);
	}
	if (init_semaphores(args))
	{
		sem_close(args->pids_sem);
		sem_unlink("/philo_pids_sem");
		return (1);
	}
	if (init_philos(args))
	{
		sem_close(args->pids_sem);
		sem_unlink("/philo_pids_sem");
		return (1);
	}
	return (0);
}

int	init_data(t_args *args)
{
	args->someone_dead = 0;
	args->finished_count = 0;
	args->start_time = 0;
	args->forks = NULL;
	args->print_sem = NULL;
	args->meal_sem = NULL;
	args->stop_sem = NULL;
	args->finished_sem = NULL;
	args->philos = NULL;
	args->pids = NULL;
	return (init_data_components(args));
}
