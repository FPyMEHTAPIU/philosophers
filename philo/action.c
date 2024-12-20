/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:17:50 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/20 13:29:55 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sleep_check(t_philo *philo, char *mes, int action_time)
{
	size_t	sleep_time;
	size_t	time;

	time = get_time();
	print_message(philo, mes, time - philo->obj->start_time, 0);
	time = get_time();
	sleep_time = time + action_time;
	while (time < sleep_time)
	{
		if (is_simulation(philo->obj) == 0)
			break ;
		usleep(1000);
		time = get_time();
	}
}

static int	try_to_eat(t_philo *temp, size_t *time)
{
	if (lock_forks(temp, time, temp->obj->start_time) == 0)
		return (0);
	if (is_simulation(temp->obj) == 0)
	{
		unlock_forks(temp);
		return (0);
	}
	pthread_mutex_lock(&temp->meal_lock);
	*time = get_time();
	temp->last_meal_time = *time;
	temp->meals_eaten++;
	pthread_mutex_unlock(&temp->meal_lock);
	print_message(temp, "is eating", *time - temp->obj->start_time, 0);
	usleep(temp->data.time_to_eat * 1000);
	unlock_forks(temp);
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
		usleep(50);
	while (is_simulation(temp->obj) != 0)
	{
		time = get_time();
		print_message(temp, "is thinking", time - temp->obj->start_time, 0);
		if (!try_to_eat(temp, &time))
			break ;
		if (is_simulation(temp->obj) == 0)
			break ;
		sleep_check(temp, "is sleeping", temp->data.time_to_sleep);
	}
	return (NULL);
}
