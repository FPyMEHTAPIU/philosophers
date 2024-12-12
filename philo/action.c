/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:17:50 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/12 17:46:36 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static size_t	get_time(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
// }

void	*start_routine(void *philo)
{
	t_philo	*temp;
	//size_t	time;

	temp = (t_philo *) philo;
	//while (!temp->is_dead && temp->meals_eaten != temp->data.meals)
	/*while (1)
	{
		pthread_mutex_lock(temp->left_fork);
		time = get_time();
		printf("%zu %d has taken a fork\n", time, temp->id);
		pthread_mutex_lock(temp->right_fork);
		time = get_time();
		printf("%zu %d has taken a fork\n", time, temp->id);
		pthread_mutex_unlock(temp->right_fork);
		pthread_mutex_unlock(temp->left_fork);
	}*/
	return (NULL);
}

// int	check_forks(t_holder *obj, int index)
// {
// 	//TODO: lock [0] fork
// 	// 	if succeed try to lock [1] fork
// 	// 		if succeed - return
// 	//		if failed - unlock [0] fork 
// }

/*void	action(t_holder *obj)
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
}*/
