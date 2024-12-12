/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:02:02 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/12 15:40:31 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_struct(t_holder *obj)
{
	int	i;

	if (!obj)
		return ;
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
		free(obj->philos);
		obj->philos = NULL;
	}
	i = obj->data.num_philos;
	while (i--)
	{
		pthread_mutex_destroy(&obj->forks[i]);
		pthread_detach(obj->threads[i]);
	}
}
