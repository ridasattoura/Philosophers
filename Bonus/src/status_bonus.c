/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 08:35:00 by ader              #+#    #+#             */
/*   Updated: 2025/07/20 08:53:40 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	check_if_dead(t_args *args)
{
	int	dead;

	sem_wait(args->stop_sem);
	dead = args->someone_dead;
	sem_post(args->stop_sem);
	return (dead);
}
