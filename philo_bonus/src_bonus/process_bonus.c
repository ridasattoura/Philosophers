/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:24:22 by risattou          #+#    #+#             */
/*   Updated: 2025/07/23 15:12:15 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	if (check_if_dead(philo->args))
		return ;
	sem_wait(philo->args->forks);
	print_status(philo, "has taken a fork");
	if (check_if_dead(philo->args))
	{
		sem_post(philo->args->forks);
		return ;
	}
	sem_wait(philo->args->forks);
	print_status(philo, "has taken a fork");
	if (check_if_dead(philo->args))
	{
		sem_post(philo->args->forks);
		sem_post(philo->args->forks);
		return ;
	}
	print_status(philo, "is eating");
	sem_wait(philo->args->meal_sem);
	philo->last_meal = get_time_ms();
	philo->nb_eat++;
	sem_post(philo->args->meal_sem);
	ft_usleep(philo->args->time_to_eat);
	sem_post(philo->args->forks);
	sem_post(philo->args->forks);
}

static int	handle_finished_eating(t_philo *philo)
{
	if (philo->args->nb_of_eat == -1)
		return (0);
	sem_wait(philo->args->meal_sem);
	if (philo->nb_eat >= philo->args->nb_of_eat)
	{
		sem_post(philo->args->meal_sem);
		exit(0);
	}
	sem_post(philo->args->meal_sem);
	return (0);
}

static int	init_philosopher_process(t_philo *philo, pthread_t *death_thread)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->args->time_to_eat / 2);
	sem_wait(philo->args->meal_sem);
	philo->last_meal = get_time_ms();
	sem_post(philo->args->meal_sem);
	if (pthread_create(death_thread, NULL, death_monitor, philo))
	{
		printf("Error: Failed to create death monitor thread\n");
		exit(1);
	}
	return (0);
}

static void	run_philosopher_loop(t_philo *philo)
{
	while (!check_if_dead(philo->args))
	{
		philo_eat(philo);
		if (check_if_dead(philo->args) || handle_finished_eating(philo))
			break ;
		philo_sleep(philo);
		if (check_if_dead(philo->args))
			break ;
		philo_think(philo);
	}
}

void	philosopher_process(t_philo *philo)
{
	pthread_t	death_thread;

	if (philo->args->nb_of_philo == 1)
	{
		single_philosopher_process(philo);
		return ;
	}
	init_philosopher_process(philo, &death_thread);
	run_philosopher_loop(philo);
	pthread_join(death_thread, NULL);
}
