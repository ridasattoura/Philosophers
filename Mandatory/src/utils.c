/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:52 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 05:24:53 by risattou         ###   ########.fr       */
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

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->args->write_mutex);
	
	if (!philo->args->someone_dead)
	{
		timestamp = get_time_ms() - philo->args->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, status);
		fflush(stdout);
	}
	
	pthread_mutex_unlock(&philo->args->write_mutex);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;

	if (!str)
		return (0);
	
	result = 0;
	sign = 1;
	i = 0;
	
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
		   str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647 && sign == 1)
			return (2147483647);
		if (result > 2147483648 && sign == -1)
			return (-2147483648);
		i++;
	}
	
	return ((int)(result * sign));
}

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
	args->start_time = get_time_ms();
	
	return (0);
}
