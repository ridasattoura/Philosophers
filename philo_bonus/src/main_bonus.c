/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:12 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 12:26:55 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	kill_all_processes(t_args *args)
{
	int	i;

	pthread_mutex_lock(&args->pids_mutex);
	i = 0;
	while (i < args->nb_of_philo)
	{
		if (args->pids[i] > 0)
			kill(args->pids[i], SIGKILL);
		i++;
	}
	pthread_mutex_unlock(&args->pids_mutex);
}

static int	create_philosophers(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_of_philo)
	{
		args->pids[i] = fork();
		if (args->pids[i] == 0)
		{
			philosopher_process(&args->philos[i]);
			exit(0);
		}
		else if (args->pids[i] < 0)
		{
			printf("Error: Failed to create philosopher process\n");
			kill_all_processes(args);
			cleanup_data(args);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	create_monitor_thread(t_args *args, pthread_t *monitor_thread)
{
	if (pthread_create(monitor_thread, NULL, monitor_routine, args))
	{
		printf("Error: Failed to create monitor thread\n");
		kill_all_processes(args);
		cleanup_data(args);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_args		args;
	pthread_t	monitor_thread;

	memset(&args, 0, sizeof(t_args));
	unlink_semaphores();
	if (parse_arguments(argc, argv, &args))
		return (1);
	if (init_data(&args))
	{
		cleanup_data(&args);
		return (1);
	}
	args.start_time = get_time_ms();
	if (create_philosophers(&args))
		return (1);
	if (create_monitor_thread(&args, &monitor_thread))
		return (1);
	pthread_join(monitor_thread, NULL);
	cleanup_data(&args);
	return (0);
}
