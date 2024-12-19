/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:02:02 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/19 16:30:51 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_philo_mtxs(t_holder *obj)
{
	int	i;

	i = 0;
	while (i < obj->data.num_philos)
	{
		pthread_mutex_destroy(&obj->philos[i].meal_lock);
		i++;
	}
}

static void	destroy_threads_mutexes(t_holder *obj)
{
	int	i;

	i = obj->data.num_philos;
	while (i--)
		pthread_join(obj->threads[i], NULL);
	pthread_join(obj->monitor, NULL);
	i = obj->data.num_philos;
	while (i--)
		pthread_mutex_destroy(&obj->forks[i]);
	pthread_mutex_destroy(&obj->message_lock);
	pthread_mutex_destroy(&obj->simulation_lock);
}

void	clean_struct(t_holder *obj)
{
	if (!obj)
		return ;
	destroy_threads_mutexes(obj);
	if (obj->forks)
	{
		free(obj->forks);
		obj->forks = NULL;
	}
	if (obj->threads)
	{
		free(obj->threads);
		obj->threads = NULL;
	}
	if (obj->philos)
	{
		destroy_philo_mtxs(obj);
		free(obj->philos);
		obj->philos = NULL;
	}
}
