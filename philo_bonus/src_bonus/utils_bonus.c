/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:25 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 13:15:37 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

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

int	ft_atoi(const char *nptr)
{
	int					sign;
	unsigned long long	total;

	sign = 1;
	total = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		total = total * 10 + (*nptr - '0');
		if (total > 9223372036854775807 && sign == 1)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		nptr++;
	}
	return (total * sign);
}
