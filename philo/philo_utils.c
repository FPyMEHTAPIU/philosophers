/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:23:06 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/19 16:23:12 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, const char *mes, size_t time, int die)
{
	pthread_mutex_lock(&philo->obj->message_lock);
	if (is_simulation(philo->obj) == 0)
	{
		pthread_mutex_unlock(&philo->obj->message_lock);
		return ;
	}
	printf("%zu %d %s\n", time, philo->id, mes);
	if (die == 1)
	{
		set_simulation_end(philo->obj);
		pthread_mutex_unlock(&philo->obj->message_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->obj->message_lock);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	is_simulation(t_holder *obj)
{
	pthread_mutex_lock(&obj->simulation_lock);
	if (obj->is_simulation == 0)
	{
		pthread_mutex_unlock(&obj->simulation_lock);
		return (0);
	}
	pthread_mutex_unlock(&obj->simulation_lock);
	return (1);
}
