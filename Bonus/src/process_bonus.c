#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	if (check_if_dead(philo->args))
		return;
	
	sem_wait(philo->args->forks);
	print_status(philo, "has taken a fork");
	
	if (check_if_dead(philo->args))
	{
		sem_post(philo->args->forks);
		return;
	}
	
	sem_wait(philo->args->forks);
	print_status(philo, "has taken a fork");
	
	if (check_if_dead(philo->args))
	{
		sem_post(philo->args->forks);
		sem_post(philo->args->forks);
		return;
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

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->args->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	*death_monitor(void *arg)
{
	t_philo		*philo;
	long long	current_time;
	long long	time_since_last_meal;

	philo = (t_philo *)arg;
	
	while (!check_if_dead(philo->args))
	{
		current_time = get_time_ms();
		
		sem_wait(philo->args->meal_sem);
		time_since_last_meal = current_time - philo->last_meal;
		sem_post(philo->args->meal_sem);
		
		if (time_since_last_meal > philo->args->time_to_die)
		{
			sem_wait(philo->args->stop_sem);
			philo->args->someone_dead = 1;
			sem_post(philo->args->stop_sem);
			
			print_status(philo, "died");
			exit(1);
		}
		
		ft_usleep(1);
	}
	
	return (NULL);
}

void	philosopher_process(t_philo *philo)
{
	pthread_t	death_thread;

	if (philo->id % 2 == 0)
		ft_usleep(10);
	
	sem_wait(philo->args->meal_sem);
	philo->last_meal = get_time_ms();
	sem_post(philo->args->meal_sem);
	
	if (pthread_create(&death_thread, NULL, death_monitor, philo))
	{
		printf("Error: Failed to create death monitor thread\n");
		exit(1);
	}
	
	while (!check_if_dead(philo->args))
	{
		philo_eat(philo);
		
		if (check_if_dead(philo->args))
			break;
		
		if (philo->args->nb_of_eat != -1)
		{
			sem_wait(philo->args->meal_sem);
			if (philo->nb_eat >= philo->args->nb_of_eat)
			{
				sem_post(philo->args->meal_sem);
				
				sem_wait(philo->args->finished_sem);
				philo->args->finished_count++;
				if (philo->args->finished_count >= philo->args->nb_of_philo)
				{
					sem_wait(philo->args->stop_sem);
					philo->args->someone_dead = 1;
					sem_post(philo->args->stop_sem);
				}
				sem_post(philo->args->finished_sem);
				break;
			}
			sem_post(philo->args->meal_sem);
		}
		
		philo_sleep(philo);
		
		if (check_if_dead(philo->args))
			break;
		
		philo_think(philo);
	}
	
	pthread_join(death_thread, NULL);
}
