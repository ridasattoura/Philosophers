/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:12 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 05:24:13 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_valid_number(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	
	i = 0;
	if (str[i] == '+')
		i++;
	
	if (!str[i])
		return (0);
	
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	
	return (1);
}

int	parse_arguments(int argc, char **argv, t_args *args)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	
	if (!is_valid_number(argv[1]) || !is_valid_number(argv[2]) || 
		!is_valid_number(argv[3]) || !is_valid_number(argv[4]) ||
		(argc == 6 && !is_valid_number(argv[5])))
	{
		printf("Error: All arguments must be positive integers\n");
		return (1);
	}
	
	args->nb_of_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	
	if (argc == 6)
		args->nb_of_eat = ft_atoi(argv[5]);
	else
		args->nb_of_eat = -1;
	
	if (args->nb_of_philo <= 0 || args->time_to_die <= 0 || 
		args->time_to_eat <= 0 || args->time_to_sleep <= 0 ||
		(argc == 6 && args->nb_of_eat <= 0))
	{
		printf("Error: All arguments must be positive integers\n");
		return (1);
	}
	
	if (args->nb_of_philo > 200)
	{
		printf("Error: Too many philosophers (max 200)\n");
		return (1);
	}
	
	args->someone_dead = 0;
	return (0);
}

void	kill_all_processes(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_of_philo)
	{
		if (args->pids[i] > 0)
			kill(args->pids[i], SIGTERM);
		i++;
	}
}

int	wait_for_processes(t_args *args)
{
	int		i;
	int		status;
	pid_t	wpid;

	i = 0;
	while (i < args->nb_of_philo)
	{
		wpid = waitpid(args->pids[i], &status, 0);
		if (wpid == -1)
		{
			perror("waitpid");
			return (1);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			kill_all_processes(args);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_args		args;
	pthread_t	monitor_thread;
	int			i;

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
	
	i = 0;
	while (i < args.nb_of_philo)
	{
		args.pids[i] = fork();
		if (args.pids[i] == 0)
		{
			philosopher_process(&args.philos[i]);
			exit(0);
		}
		else if (args.pids[i] < 0)
		{
			printf("Error: Failed to create philosopher process\n");
			kill_all_processes(&args);
			cleanup_data(&args);
			return (1);
		}
		i++;
	}
	
	if (pthread_create(&monitor_thread, NULL, monitor_routine, &args))
	{
		printf("Error: Failed to create monitor thread\n");
		kill_all_processes(&args);
		cleanup_data(&args);
		return (1);
	}
	
	pthread_join(monitor_thread, NULL);
	
	wait_for_processes(&args);
	
	cleanup_data(&args);
	return (0);
}
