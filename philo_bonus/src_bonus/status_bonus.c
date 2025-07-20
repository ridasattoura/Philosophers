/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:10:50 by risattou          #+#    #+#             */
/*   Updated: 2025/07/20 13:10:52 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

int	check_if_dead(t_args *args)
{
	int	dead;

	sem_wait(args->stop_sem);
	dead = args->someone_dead;
	sem_post(args->stop_sem);
	return (dead);
}
