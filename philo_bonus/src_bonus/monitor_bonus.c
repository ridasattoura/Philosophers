/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:15 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 13:08:41 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

int	check_meals_completion(t_args *args)
{
	int	i;
	int	total_meals_eaten;

	if (args->nb_of_eat == -1)
		return (0);
	i = 0;
	total_meals_eaten = 0;
	sem_wait(args->meal_sem);
	while (i < args->nb_of_philo)
	{
		if (args->philos[i].nb_eat >= args->nb_of_eat)
			total_meals_eaten++;
		i++;
	}
	sem_post(args->meal_sem);
	if (total_meals_eaten >= args->nb_of_philo)
	{
		sem_wait(args->stop_sem);
		args->someone_dead = 1;
		sem_post(args->stop_sem);
		return (1);
	}
	return (0);
}

static void	handle_process_death(t_args *args, pid_t dead_pid)
{
	int	i;

	sem_wait(args->stop_sem);
	args->someone_dead = 1;
	sem_post(args->stop_sem);
	pthread_mutex_lock(&args->pids_mutex);
	i = 0;
	while (i < args->nb_of_philo)
	{
		if (args->pids[i] > 0 && args->pids[i] != dead_pid)
		{
			kill(args->pids[i], SIGKILL);
			args->pids[i] = -1;
		}
		i++;
	}
	pthread_mutex_unlock(&args->pids_mutex);
}

static int	handle_process_completion(t_args *args, int *finished_count)
{
	if (args->nb_of_eat == -1)
		return (0);
	if (*finished_count >= args->nb_of_philo)
	{
		sem_wait(args->stop_sem);
		args->someone_dead = 1;
		sem_post(args->stop_sem);
		return (1);
	}
	return (0);
}

static int	process_child_status(t_args *args, pid_t wpid, int status,
		int *finished_count)
{
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
	{
		handle_process_death(args, wpid);
		return (1);
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		(*finished_count)++;
		return (handle_process_completion(args, finished_count));
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_args	*args;
	int		status;
	pid_t	wpid;
	int		finished_count;

	args = (t_args *)arg;
	finished_count = 0;
	ft_usleep(1);
	while (!check_if_dead(args))
	{
		wpid = waitpid(-1, &status, WNOHANG);
		if (wpid > 0)
		{
			if (process_child_status(args, wpid, status, &finished_count))
				break ;
		}
		else if (wpid == -1 && finished_count > 0)
			break ;
		ft_usleep(1);
	}
	return (NULL);
}
