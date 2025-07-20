#include "../includes/philo.h"

void	clean_simulation(t_args *args, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	if (forks)
	{
		i = 0;
		while (i < args->nb_of_philo)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
		free(forks);
	}

	pthread_mutex_destroy(&args->write_mutex);

	if (philos)
		free(philos);
}
