#include "philo_bonus.h"

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

void	*monitor_routine(void *arg)
{
	t_args	*args;
	int		status;
	pid_t	wpid;

	args = (t_args *)arg;
	
	ft_usleep(1);
	
	while (!check_if_dead(args))
	{
		wpid = waitpid(-1, &status, WNOHANG);
		if (wpid > 0)
		{
			if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			{
				sem_wait(args->stop_sem);
				args->someone_dead = 1;
				sem_post(args->stop_sem);
				break;
			}
		}
		else if (wpid == -1)
		{
			break;
		}
		
		ft_usleep(10);
	}
	
	return (NULL);
}
