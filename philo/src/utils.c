/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:52 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 15:38:46 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int time)
{
	long long	start;
	long long	end;

	start = get_time_ms();
	end = start + time;
	while (get_time_ms() < end)
	{
		usleep(100);
	}
}

void	ft_usleep_safe(int time, t_args *args)
{
	long long	start;
	long long	end;

	start = get_time_ms();
	end = start + time;
	while (get_time_ms() < end)
	{
		if (check_if_dead(args))
			break ;
		usleep(100);
	}
}

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->args->write_mutex);
	if (!philo->args->someone_dead)
	{
		timestamp = get_time_ms() - philo->args->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->args->write_mutex);
}

int	check_if_dead(t_args *args)
{
	pthread_mutex_lock(&args->write_mutex);
	if (args->someone_dead)
	{
		pthread_mutex_unlock(&args->write_mutex);
		return (1);
	}
	pthread_mutex_unlock(&args->write_mutex);
	return (0);
}
