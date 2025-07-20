/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:50 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 13:10:20 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->args->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
}

static void	take_forks_even(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	if (check_if_dead(philo->args))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
}

static void	take_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	if (check_if_dead(philo->args))
	{
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
}

static void	eat_process(t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_ms();
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->args->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_status(philo, "is sleeping");
	ft_usleep_safe(philo->args->time_to_sleep, philo->args);
}

void	eat_and_sleep(t_philo *philo)
{
	if (check_if_dead(philo->args))
		return ;
	if (philo->args->nb_of_philo == 1)
	{
		handle_single_philo(philo);
		return ;
	}
	if (philo->id % 2 == 0)
		take_forks_even(philo);
	else
		take_forks_odd(philo);
	if (check_if_dead(philo->args))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	eat_process(philo);
}
