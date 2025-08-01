/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:44 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 16:34:20 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

	if (parse_arguments(argc, argv, &args) != 0)
		return (1);
	return (simulation(&args));
}
