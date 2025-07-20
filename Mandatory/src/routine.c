#include "../includes/philo.h"

void	eat_and_sleep(t_philo *philo)
{
	if (check_if_dead(philo->args))
		return;

	if (philo->args->nb_of_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		ft_usleep(philo->args->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return;
	}

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		if (check_if_dead(philo->args))
		{
			pthread_mutex_unlock(philo->left_fork);
			return;
		}
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		if (check_if_dead(philo->args))
		{
			pthread_mutex_unlock(philo->right_fork);
			return;
		}
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}

	if (check_if_dead(philo->args))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return;
	}

	print_status(philo, "is eating");
	philo->last_meal = get_time_ms();
	philo->nb_eat++;

	ft_usleep(philo->args->time_to_eat);

	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);

	print_status(philo, "is sleeping");
	ft_usleep(philo->args->time_to_sleep);
}

void	*start_routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;

	if (ph->id % 2 == 0)
		ft_usleep(ph->args->time_to_eat / 2);

	while (!check_if_dead(ph->args))
	{
		print_status(ph, "is thinking");
		
		int cycle_time = ph->args->time_to_eat + ph->args->time_to_sleep;
		int safe_think_time = 0;
		
		if (ph->args->nb_of_philo % 2 == 1 && ph->args->nb_of_philo > 3)
		{
			int max_safe_think = ph->args->time_to_die - cycle_time - 50;
			if (max_safe_think > 0)
			{
				safe_think_time = ph->args->time_to_eat / 2;
				if (safe_think_time > max_safe_think)
					safe_think_time = max_safe_think;
				
				if (safe_think_time > 0)
					ft_usleep(safe_think_time);
			}
		}

		eat_and_sleep(ph);

		if (ph->args->nb_of_eat != -1 && ph->nb_eat >= ph->args->nb_of_eat)
			break;
	}

	return (NULL);
}
