/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:35:52 by risattou          #+#    #+#             */
/*   Updated: 2025/08/03 06:08:25 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	display_error(void)
{
	write(2, "Error! invalid arguments\n", 26);
	return (1);
}

int	main(int argc, char *argv[])
{
	int			i;
	t_table		table;

	if ((argc < 5 || argc > 6) || validate_args(argc, argv, &table))
		return (display_error());
	table.start_time = get_current_time();
	i = -1;
	while (++i < table.nb_philos)
	{
		table.philos[i].process_id = fork();
		if (table.philos[i].process_id == -1)
		{
			write(2, "Error! fork failed\n", 19);
			exit(1);
		}
		if (table.philos[i].process_id == 0)
			philosopher_routine((void *)&table.philos[i]);
	}
	sem_wait(table.death_sem);
	i = -1;
	while (++i < table.nb_philos)
		kill(table.philos[i].process_id, SIGTERM);
	cleanup_and_exit(&table);
	return (0);
}
