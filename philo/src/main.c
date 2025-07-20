/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:44 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 13:10:11 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die ", av[0]);
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	i = 1;
	while (i < ac)
	{
		if (!is_valid_number(av[i]))
		{
			printf("Error: All arguments must be positive integers\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	create_threads(t_philo *philos, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_of_philo)
	{
		if (pthread_create(&philos[i].thread, NULL,
				&start_routine, &philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&args->monitoring_thread, NULL,
			&monitoring, philos) != 0)
		return (1);
	return (0);
}

static void	join_threads(t_philo *philos, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_of_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(args->monitoring_thread, NULL);
}

int	simulation(t_args *args)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (init_philo(&philos, args, &forks) != 0)
		return (1);
	if (create_threads(philos, args) != 0)
	{
		clean_simulation(args, philos, forks);
		return (1);
	}
	join_threads(philos, args);
	clean_simulation(args, philos, forks);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	args;

	if (check_args(argc, argv) != 0)
		return (1);
	if (parse_arguments(argc, argv, &args) != 0)
		return (1);
	return (simulation(&args));
}
