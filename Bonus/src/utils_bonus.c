/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:25 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 08:53:45 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int time)
{
	long long	start;

	start = get_time_ms();
	while (get_time_ms() - start < time)
		usleep(100);
}

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	sem_wait(philo->args->print_sem);
	if (!check_if_dead(philo->args))
	{
		timestamp = get_time_ms() - philo->args->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, status);
	}
	sem_post(philo->args->print_sem);
}

static int	ft_atoi_convert(const char *str, long result, int sign, int i)
{
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
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (ft_atoi_convert(str, result, sign, i));
}
