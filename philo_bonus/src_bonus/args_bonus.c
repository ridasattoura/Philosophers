/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:09:19 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 13:09:24 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

int	is_valid_number(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	validate_argument_count(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die ", argv[0]);
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	return (0);
}

static int	validate_argument_format(int argc, char **argv)
{
	if (!is_valid_number(argv[1]) || !is_valid_number(argv[2])
		|| !is_valid_number(argv[3]) || !is_valid_number(argv[4]) || (argc == 6
			&& !is_valid_number(argv[5])))
	{
		printf("Error: All arguments must be positive integers\n");
		return (1);
	}
	return (0);
}

static int	validate_argument_values(t_args *args, int argc)
{
	if (args->nb_of_philo <= 0 || args->time_to_die <= 0
		|| args->time_to_eat <= 0 || args->time_to_sleep <= 0 || (argc == 6
			&& args->nb_of_eat <= 0))
	{
		printf("Error: All arguments must be positive integers\n");
		return (1);
	}
	if (args->nb_of_philo > 200)
	{
		printf("Error: Too many philosophers (max 200)\n");
		return (1);
	}
	if (args->time_to_die > 60000 || args->time_to_eat > 60000
		|| args->time_to_sleep > 60000)
	{
		printf("Error: Time values too large (max 60000ms)\n");
		return (1);
	}
	if (argc == 6 && args->nb_of_eat > 10000)
	{
		printf("Error: Meal count too large (max 10000)\n");
		return (1);
	}
	return (0);
}

int	parse_arguments(int argc, char **argv, t_args *args)
{
	if (validate_argument_count(argc, argv))
		return (1);
	if (validate_argument_format(argc, argv))
		return (1);
	args->nb_of_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nb_of_eat = ft_atoi(argv[5]);
	else
		args->nb_of_eat = -1;
	if (validate_argument_values(args, argc))
		return (1);
	args->someone_dead = 0;
	return (0);
}
