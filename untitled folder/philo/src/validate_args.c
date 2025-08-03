/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valider_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:27:35 by risattou          #+#    #+#             */
/*   Updated: 2025/08/03 02:34:51 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static int	validate_args(int argc, char *argv[])
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
	return (0);
}

static void	initialize_simulation(t_dining_table *table)
{
	int	i;

	table->someone_died = 0;
	table->all_satisfied = 0;
	table->philosophers = (t_philosopher *)malloc(table->philo_count
			* sizeof(t_philosopher));
	i = -1;
	while (++i < table->philo_count)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].table = table;
		table->philosophers[i].meals_eaten = 0;
		if (i + 1 == table->philo_count)
			table->philosophers[i].next = &table->philosophers[0];
		else
			table->philosophers[i].next = &table->philosophers[i + 1];
		if (i == 0)
			table->philosophers[i].prev 
				= &table->philosophers[table->philo_count - 1];
		else
			table->philosophers[i].prev = &table->philosophers[i - 1];
		pthread_mutex_init(&table->philosophers[i].fork, NULL);
	}
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->check_mutex, NULL);
}

int	validate_arguments(int argc, char *argv[], t_dining_table *table)
{
	if (validate_args(argc, argv))
		return (1);
	table->philo_count = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->max_meals = -1;
	if (argc == 6)
		table->max_meals = ft_atoi(argv[5]);
	initialize_simulation(table);
	return (0);
}
