/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:17:50 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/13 17:29:46 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_forks(t_philo *philo, size_t *time, size_t start_time)
{
	*time = get_time();
	pthread_mutex_lock(&philo->meal_lock);
	if (*time - philo->last_meal_time >= (size_t) philo->data.time_to_die)
	{
		printf("check 1\n");
		pthread_mutex_lock(&philo->message_lock);
		printf("%zu %d died\n", *time - start_time, philo->id);
		philo->is_dead = 1;
		pthread_mutex_unlock(&philo->message_lock);
		pthread_mutex_unlock(&philo->meal_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->message_lock);
		printf("%zu %d has taken a fork\n", *time - start_time, philo->id);
		pthread_mutex_unlock(&philo->message_lock);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->message_lock);
		printf("%zu %d has taken a fork\n", *time - start_time, philo->id);
		pthread_mutex_unlock(&philo->message_lock);
		pthread_mutex_lock(philo->left_fork);
	}
	*time = get_time();
	pthread_mutex_lock(&philo->message_lock);
	printf("%zu %d has taken a fork\n", *time - start_time, philo->id);
	pthread_mutex_unlock(&philo->message_lock);
	return (1);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	is_simulation(t_philo *obj)
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

void	*start_routine(void *philo)
{
	t_philo	*temp;
	size_t	time;
	size_t	start_time;

	temp = (t_philo *) philo;
	start_time = get_time();
	while (is_simulation(temp) != 0)
	{
		if (is_simulation(temp) != 0)
		{
			time = get_time();
			pthread_mutex_lock(&temp->message_lock);
			printf("%zu %d is thinking\n", time - start_time, temp->id);
			pthread_mutex_unlock(&temp->message_lock);
		}
		if (temp->meals_eaten == 0)
		{
			pthread_mutex_lock(&temp->meal_lock);
			temp->last_meal_time = get_time();
			pthread_mutex_unlock(&temp->meal_lock);
		}
			
		if (is_simulation(temp) == 0 || !lock_forks(temp, &time, start_time))
			break ;
		time = get_time();
		if (time - temp->last_meal_time >= (size_t) temp->data.time_to_die)
		{
			pthread_mutex_lock(&temp->message_lock);
			printf("%zu %d died\n", time - start_time, temp->id);
			temp->is_dead = 1;
			pthread_mutex_unlock(&temp->message_lock);
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
		pthread_mutex_lock(&temp->message_lock);
		printf("%zu %d is eating\n", time - start_time, temp->id);
		pthread_mutex_unlock(&temp->message_lock);
		usleep(temp->data.time_to_eat * 1000);
		pthread_mutex_unlock(temp->right_fork);
		pthread_mutex_unlock(temp->left_fork);
		pthread_mutex_lock(&temp->meal_lock);
		temp->last_meal_time = get_time();
		temp->meals_eaten++;
		pthread_mutex_unlock(&temp->meal_lock);
		time = get_time();
		pthread_mutex_lock(&temp->message_lock);
		printf("%zu %d is sleeping\n", time - start_time, temp->id);
		pthread_mutex_unlock(&temp->message_lock);
		usleep(temp->data.time_to_sleep * 1000);
	}
	return (NULL);
}
