/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:36:14 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/12 12:56:35 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_holder *obj)
{
	int		i;

	obj->philos = malloc(sizeof(t_philo) * obj->num_philos);
	if (!obj->philos)
		return (0);
	i = 0;
	while (i < obj->num_philos)
	{
		if (pthread_mutex_init(&obj->forks[i], NULL) != 0)
		{
			while (i--)
				pthread_mutex_destroy(&obj->forks[i]);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < obj->num_philos)
	{
		if (pthread_create(&obj->threads[i], NULL, NULL, NULL) != 0)
		{
			while (i--)
				pthread_detach(&obj->threads[i]);
			return (0);
		}
		i++;
	}
}

t_holder	init_holder(char **argv)
{
	t_holder	obj;

	obj.init_err = 1;
	if (parse_args(&obj, argv) != 0)
		return (obj);
	obj.threads = malloc(sizeof(pthread_t) * obj.num_philos);
	if (!obj.threads)
	{
		write_err(4);
		return (obj);
	}
	obj.forks = malloc(sizeof(pthread_mutex_t) * obj.num_philos);
	if (!obj.forks)
	{
		free(obj.threads);
		write_err(4);
		return (obj);
	}
	obj.init_err = 0;
	obj.philo_dead = 0;
	return (obj);
}