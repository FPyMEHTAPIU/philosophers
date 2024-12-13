/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:17:50 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/13 16:25:02 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*start_routine(void *philo)
{
	t_philo	*temp;
	size_t	time;
	size_t	start_time;

	temp = (t_philo *) philo;
	start_time = get_time();
	while (temp->is_simulation != 0)
	{
		if (temp->meals_eaten > 0)
		{
			time = get_time();
			printf("%zu %d is thinking\n", time - start_time, temp->id);
		}
		if (temp->meals_eaten == 0)
		{
			pthread_mutex_lock(&temp->meal_lock);
			temp->last_meal_time = get_time();
			pthread_mutex_unlock(&temp->meal_lock);
		}
			
		time = get_time();
		if (time - temp->last_meal_time >= (size_t) temp->data.time_to_die)
		{
			printf("check 1\n");
			pthread_mutex_lock(&temp->die_lock);
			printf("%zu %d died\n", time - start_time, temp->id);
			temp->is_dead = 1;
			pthread_mutex_unlock(&temp->die_lock);
			break;
		}

		if (temp->id % 2 == 1)
		{
			pthread_mutex_lock(temp->left_fork);
			printf("%zu %d has taken a fork\n", time - start_time, temp->id);
			pthread_mutex_lock(temp->right_fork);
		}
		else
		{
			pthread_mutex_lock(temp->right_fork);
			printf("%zu %d has taken a fork\n", time - start_time, temp->id);
			pthread_mutex_lock(temp->left_fork);
		}
		time = get_time();
		printf("%zu %d has taken a fork\n", time - start_time, temp->id);
		time = get_time();
		if (time - temp->last_meal_time >= (size_t) temp->data.time_to_die)
		{
			printf("check 2\n");
			pthread_mutex_lock(&temp->die_lock);
			printf("%zu %d died\n", time - start_time, temp->id);
			temp->is_dead = 1;
			pthread_mutex_unlock(&temp->die_lock);
			if (temp->id % 2 == 1)
			{
				pthread_mutex_unlock(temp->right_fork);
				pthread_mutex_unlock(temp->left_fork);
			}
			else
			{
				pthread_mutex_unlock(temp->left_fork);
				pthread_mutex_unlock(temp->right_fork);
			}
			break;
		}
		printf("%zu %d is eating\n", time - start_time, temp->id);
		usleep(temp->data.time_to_eat * 1000);
		pthread_mutex_lock(&temp->meal_lock);
		temp->last_meal_time = get_time();
		(temp->meals_eaten)++;
		pthread_mutex_unlock(&temp->meal_lock);
		pthread_mutex_unlock(temp->right_fork);
		pthread_mutex_unlock(temp->left_fork);
		time = get_time();
		printf("%zu %d is sleeping\n", time - start_time, temp->id);
		usleep(temp->data.time_to_sleep * 1000);
	}
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
