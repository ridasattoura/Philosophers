/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_monitor_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 08:40:00 by ader              #+#    #+#             */
/*   Updated: 2025/07/20 08:53:27 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	check_process_status(t_args *args, int i, int *finished_count)
{
	int		status;
	pid_t	wpid;

	if (args->pids[i] <= 0)
		return (0);
	wpid = waitpid(args->pids[i], &status, WNOHANG);
	if (wpid > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			pthread_mutex_unlock(&args->pids_mutex);
			kill_all_processes(args);
			return (1);
		}
		args->pids[i] = -1;
		(*finished_count)++;
	}
	else if (wpid == -1)
	{
		pthread_mutex_unlock(&args->pids_mutex);
		perror("waitpid");
		return (1);
	}
	return (0);
}

int	wait_for_processes(t_args *args)
{
	int		i;
	int		finished_count;
	int		result;

	finished_count = 0;
	while (finished_count < args->nb_of_philo)
	{
		i = 0;
		while (i < args->nb_of_philo)
		{
			pthread_mutex_lock(&args->pids_mutex);
			result = check_process_status(args, i, &finished_count);
			if (result)
				return (result);
			pthread_mutex_unlock(&args->pids_mutex);
			i++;
		}
		usleep(1000);
	}
	return (0);
}
