#include "philo_bonus.h"

void	unlink_semaphores(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_FINISHED);
}

void	destroy_semaphores(t_args *args)
{
	if (args->forks && args->forks != SEM_FAILED)
		sem_close(args->forks);
	
	if (args->print_sem && args->print_sem != SEM_FAILED)
		sem_close(args->print_sem);
	
	if (args->meal_sem && args->meal_sem != SEM_FAILED)
		sem_close(args->meal_sem);
	
	if (args->stop_sem && args->stop_sem != SEM_FAILED)
		sem_close(args->stop_sem);
	
	if (args->finished_sem && args->finished_sem != SEM_FAILED)
		sem_close(args->finished_sem);
	
	unlink_semaphores();
}

void	cleanup_data(t_args *args)
{
	destroy_semaphores(args);
	
	if (args->philos)
	{
		free(args->philos);
		args->philos = NULL;
	}
	
	if (args->pids)
	{
		free(args->pids);
		args->pids = NULL;
	}
}
