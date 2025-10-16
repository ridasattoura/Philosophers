/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:27:21 by risattou          #+#    #+#             */
/*   Updated: 2025/08/03 02:32:55 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	display_error(void)
{
	write(2, "Error! invalid arguments\n", 26);
	return (1);
}

int	main(int argc, char *argv[])
{
	int				i;
	t_dining_table	table;
	pthread_t		*thread_ids;

	if ((argc < 5 || argc > 6) || validate_arguments(argc, argv, &table))
		return (display_error());
	thread_ids = (pthread_t *)malloc(table.philo_count * sizeof(pthread_t));
	table.start_time = get_current_time();
	i = -1;
	while (++i < table.philo_count)
	{
		if (pthread_create(&thread_ids[i], NULL, &philosopher_routine,
				&table.philosophers[i]))
		{
			write(2, "Error! cannot create thread\n", 28);
			free(table.philosophers);
			return (free(thread_ids), 1);
		}
		pthread_mutex_lock(&table.check_mutex);
		table.philosophers[i].last_meal_time = table.start_time;
		pthread_mutex_unlock(&table.check_mutex);
	}
	monitor_philosophers(&table);
	cleanup_and_exit(&table, thread_ids);
	return (0);
}
