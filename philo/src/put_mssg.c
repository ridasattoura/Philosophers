/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_mssg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: risattou <risattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:27:27 by risattou          #+#    #+#             */
/*   Updated: 2025/08/03 06:53:58 by risattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*get_action_message(int action)
{
	if (action == TOOK_FORK)
		return ("has taken a fork");
	if (action == IS_EATING)
		return ("is eating");
	if (action == IS_SLEEPING)
		return ("is sleeping");
	if (action == IS_THINKING)
		return ("is thinking");
	if (action == DIED)
		return ("died");
	return ("Error: not valid action id");
}

void	print_status(t_philosopher *philo, int action)
{
	size_t	elapsed_time;

	elapsed_time = get_current_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->print_mutex);
	if ((!philo->table->someone_died && !philo->table->all_satisfied)
		|| action == DIED)
	{
		printf("%ld ", elapsed_time);
		printf("%d ", philo->id);
		printf("%s", get_action_message(action));
		printf("\n");
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
}
