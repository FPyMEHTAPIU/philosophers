/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:02:02 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/13 17:08:18 by msavelie         ###   ########.fr       */
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
		pthread_mutex_destroy(&obj->philos[i].message_lock);
		pthread_mutex_destroy(&obj->philos[i].simulation_lock);
		i++;
	}
}

void	clean_struct(t_holder *obj)
{
	int	i;

	if (!obj)
		return ;
	i = obj->data.num_philos;
	while (--i)
	{
		pthread_mutex_destroy(&obj->forks[i]);
		pthread_join(obj->threads[i], NULL);
	}
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
