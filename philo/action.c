/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:17:50 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/19 11:23:51 by msavelie         ###   ########.fr       */
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

static int	lock_forks(t_philo *philo, size_t *time, size_t start_time)
{
	*time = get_time();
	pthread_mutex_lock(philo->left_fork);
	*time = get_time();
	print_message(philo, "has taken a fork", *time - start_time, 0);
	if (!is_simulation(philo->obj))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	*time = get_time();
	if (!is_simulation(philo->obj))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	print_message(philo, "has taken a fork", *time - start_time, 0);
	return (1);
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

void	*start_routine(void *philo)
{
	t_philo	*temp;
	size_t	time;

	temp = (t_philo *) philo;
	pthread_mutex_lock(&temp->meal_lock);
	temp->last_meal_time = get_time();
	pthread_mutex_unlock(&temp->meal_lock);
	if (temp->id % 2 == 0)
		usleep(100);
	while (is_simulation(temp->obj) != 0)
	{
		time = get_time();
		print_message(philo, "is thinking", time - temp->obj->start_time, 0);
	
		if (lock_forks(temp, &time, temp->obj->start_time) == 0)
			break;
		if (is_simulation(temp->obj) == 0)
			break;
		pthread_mutex_lock(&temp->meal_lock);
		time = get_time();
		temp->last_meal_time = time;
		temp->meals_eaten++;
		pthread_mutex_unlock(&temp->meal_lock);
		print_message(philo, "is eating", time - temp->obj->start_time, 0);
		usleep(temp->data.time_to_eat * 1000);
		pthread_mutex_unlock(temp->right_fork);
		pthread_mutex_unlock(temp->left_fork);
		if (is_simulation(temp->obj) == 0)
			break ;
		time = get_time();
		print_message(philo, "is sleeping", time - temp->obj->start_time, 0);
		usleep(temp->data.time_to_sleep * 1000);
	}
	return (NULL);
}
