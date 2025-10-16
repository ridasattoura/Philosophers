/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args_bonus_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:36:07 by user              #+#    #+#             */
/*   Updated: 2025/08/03 02:36:08 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_numeric_args(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		if (argv[i][0] == '-')
			return (1);
		else if (argv[i][0] == '+')
			j++;
		if (!ft_isdigit(argv[i][j + 1]))
			return (1);
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
		}
	}
	return (0);
}

static int	check_integer_overflow(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (*s == '+' && s++)
		len--;
	while (*s == '0' && *s && len--)
		s++;
	if (len > 10)
		return (1);
	else if (len < 10)
		return (0);
	if (ft_strncmp(s, "2147483648", 10) >= 0)
		return (1);
	return (0);
}

static void	init_philosophers(t_table *table)
{
	int	i;

	table->philos = (t_philo *)malloc(table->nb_philos * sizeof(t_philo));
	i = -1;
	while (++i < table->nb_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].meals_eaten = 0;
		if (i + 1 == table->nb_philos)
			table->philos[i].next = &table->philos[0];
		else
			table->philos[i].next = &table->philos[i + 1];
		if (i == 0)
			table->philos[i].prev = &table->philos[table->nb_philos - 1];
		else
			table->philos[i].prev = &table->philos[i - 1];
	}
}

static void	init_semaphores(t_table *table)
{
	sem_unlink("/sem_print");
	sem_unlink("/sem_forks");
	sem_unlink("/sem_death");
	table->print_sem = sem_open("/sem_print", O_CREAT, 0644, 1);
	table->forks_sem = sem_open("/sem_forks", O_CREAT, 0644, table->nb_philos);
	table->death_sem = sem_open("/sem_death", O_CREAT, 0644, 0);
	if (table->print_sem == SEM_FAILED || table->forks_sem == SEM_FAILED
		|| table->death_sem == SEM_FAILED)
	{
		write(2, "Error! sem_open failed\n", 23);
		exit(1);
	}
}

int	validate_args(int argc, char *argv[], t_table *table)
{
	int	i;

	if (check_numeric_args(argc, argv))
		return (1);
	i = 0;
	while (++i < argc)
	{
		if (check_integer_overflow(argv[i]))
			return (1);
	}
	table->nb_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->nb_meals = -1;
	if (argc == 6)
		table->nb_meals = ft_atoi(argv[5]);
	init_philosophers(table);
	init_semaphores(table);
	return (0);
}
