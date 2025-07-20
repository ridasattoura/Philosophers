#include "philo_bonus.h"

int	init_semaphores(t_args *args)
{
	args->forks = sem_open("/philo_forks", O_CREAT | O_EXCL, 0644, args->nb_of_philo);
	if (args->forks == SEM_FAILED)
	{
		perror("sem_open forks");
		return (1);
	}
	
	args->print_sem = sem_open("/philo_print", O_CREAT | O_EXCL, 0644, 1);
	if (args->print_sem == SEM_FAILED)
	{
		perror("sem_open print");
		sem_close(args->forks);
		sem_unlink("/philo_forks");
		return (1);
	}
	
	args->meal_sem = sem_open("/philo_meal", O_CREAT | O_EXCL, 0644, 1);
	if (args->meal_sem == SEM_FAILED)
	{
		perror("sem_open meal");
		sem_close(args->forks);
		sem_close(args->print_sem);
		sem_unlink("/philo_forks");
		sem_unlink("/philo_print");
		return (1);
	}
	
	args->stop_sem = sem_open("/philo_stop", O_CREAT | O_EXCL, 0644, 1);
	if (args->stop_sem == SEM_FAILED)
	{
		perror("sem_open stop");
		sem_close(args->forks);
		sem_close(args->print_sem);
		sem_close(args->meal_sem);
		sem_unlink("/philo_forks");
		sem_unlink("/philo_print");
		sem_unlink("/philo_meal");
		return (1);
	}
	
	args->finished_sem = sem_open("/philo_finished", O_CREAT | O_EXCL, 0644, 1);
	if (args->finished_sem == SEM_FAILED)
	{
		perror("sem_open finished");
		sem_close(args->forks);
		sem_close(args->print_sem);
		sem_close(args->meal_sem);
		sem_close(args->stop_sem);
		sem_unlink("/philo_forks");
		sem_unlink("/philo_print");
		sem_unlink("/philo_meal");
		sem_unlink("/philo_stop");
		return (1);
	}
	
	return (0);
}

int	init_philos(t_args *args)
{
	int	i;

	args->philos = malloc(sizeof(t_philo) * args->nb_of_philo);
	if (!args->philos)
		return (1);
	
	args->pids = malloc(sizeof(pid_t) * args->nb_of_philo);
	if (!args->pids)
	{
		free(args->philos);
		args->philos = NULL;
		return (1);
	}
	
	i = 0;
	while (i < args->nb_of_philo)
	{
		args->philos[i].id = i + 1;
		args->philos[i].nb_eat = 0;
		args->philos[i].last_meal = 0;
		args->philos[i].args = args;
		args->pids[i] = 0;
		i++;
	}
	
	return (0);
}

int	init_data(t_args *args)
{
	args->someone_dead = 0;
	args->finished_count = 0;
	args->start_time = 0;
	args->forks = NULL;
	args->print_sem = NULL;
	args->meal_sem = NULL;
	args->stop_sem = NULL;
	args->finished_sem = NULL;
	args->philos = NULL;
	args->pids = NULL;
	
	if (init_semaphores(args))
		return (1);
	
	if (init_philos(args))
		return (1);
	
	return (0);
}
