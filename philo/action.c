/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:17:50 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/12 12:42:01 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_routine(void *obj)
{

}

int	check_forks(t_holder *obj, int index)
{
	//TODO: lock [0] fork
	// 	if succeed try to lock [1] fork
	// 		if succeed - return
	//		if failed - unlock [0] fork 
}

void	action(t_holder *obj)
{
	int	i;

	while (obj->philo_dead == 0 && (obj->meals != 0))
	{
		i = 0;
		while (i < obj->num_philos)
		{
			if (pthread_mutex_lock(&obj->forks[i]) == 0)
			{
				if (i == obj->num_philos - 1)
				{
					if (pthread_mutex_lock(&obj->forks[0]) != 0)
						pthread_mutex_unlock(&obj->forks[0]);
				}
				else
				{
					if (pthread_mutex_lock(&obj->forks[i + 1]) != 0)
						pthread_mutex_unlock(&obj->forks[i]);
				}
			}
			i++;
		}
	}
}
