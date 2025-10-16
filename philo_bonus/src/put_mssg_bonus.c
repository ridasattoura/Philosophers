/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_mssg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:35:58 by risattou          #+#    #+#             */
/*   Updated: 2025/08/03 02:35:59 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static char	*get_action_message(int action)
{
	if (action == TOOK_FORK)
		return (" has taken a fork");
	if (action == IS_EATING)
		return (" is eating");
	if (action == IS_SLEEPING)
		return (" is sleeping");
	if (action == IS_THINKING)
		return (" is thinking");
	if (action == DIED)
		return (" died");
	return ("Error: not valid action id");
}

void	print_status(t_philo *philo, int action)
{
	long	elapsed_time;

	elapsed_time = get_current_time() - philo->table->start_time;
	sem_wait(philo->table->print_sem);
	printf("%ld ", elapsed_time);
	printf("%d ", philo->id);
	printf("%s", get_action_message(action));
	printf("\n");
	if (action != DIED)
		sem_post(philo->table->print_sem);
}
