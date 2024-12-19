/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:17:47 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/19 16:18:22 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	choose_fork_order(t_philo *philo,
	pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 1)
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	else
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
}

int	lock_forks(t_philo *philo, size_t *time, size_t start_time)
{
	pthread_mutex_t	*first_taken;
	pthread_mutex_t	*second_taken;

	*time = get_time();
	choose_fork_order(philo, &first_taken, &second_taken);
	pthread_mutex_lock(first_taken);
	*time = get_time();
	print_message(philo, "has taken a fork", *time - start_time, 0);
	if (!is_simulation(philo->obj))
	{
		pthread_mutex_unlock(first_taken);
		return (0);
	}
	pthread_mutex_lock(second_taken);
	*time = get_time();
	if (!is_simulation(philo->obj))
	{
		pthread_mutex_unlock(second_taken);
		pthread_mutex_unlock(first_taken);
		return (0);
	}
	print_message(philo, "has taken a fork", *time - start_time, 0);
	return (1);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
