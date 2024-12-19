/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:36:14 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/19 12:21:10 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_holder *obj, t_data data)
{
	int	i;

	i = 0;
	while (i < data.num_philos)
	{
		obj->philos[i].obj = obj;
		obj->philos[i].data = data;
		obj->philos[i].left_fork = &obj->forks[i];
		obj->philos[i].right_fork = &obj->forks[(i + 1) % data.num_philos];
		obj->philos[i].id = i + 1;
		obj->philos[i].meals_eaten = 0;
		pthread_mutex_init(&obj->philos[i].meal_lock, NULL);
		obj->philos[i].message_lock = &obj->message_lock;
		obj->philos[i].simulation_lock = &obj->simulation_lock;
		i++;
	}
}

static int	create_muthreads(t_holder *obj, t_data data)
{
	int	i;

	i = 0;
	while (i < data.num_philos)
	{
		if (pthread_mutex_init(&obj->forks[i], NULL) != 0)
		{
			while (i--)
				pthread_mutex_destroy(&obj->forks[i]);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&obj->message_lock, NULL) != 0 || pthread_mutex_init(&obj->simulation_lock, NULL) != 0)
	{
		while (i--)
			pthread_mutex_destroy(&obj->forks[i]);
		return (0);
	}
	assign_forks(obj, data);
	i = 0;
	pthread_mutex_lock(&obj->simulation_lock);
	obj->start_time = get_time();
	pthread_mutex_unlock(&obj->simulation_lock);
	while (i < data.num_philos)
	{
		if (pthread_create(&obj->threads[i], NULL, start_routine, (void *)&obj->philos[i]) != 0)
		{
			while (i--)
				pthread_join(obj->threads[i], NULL);
			return (0);
		}
		i++;
	}
	usleep(1000);
	pthread_create(&obj->monitor, NULL, run_monitoring, (void *)obj);
	return (1);
}

int	init_philos(t_holder *obj, t_data data)
{
	obj->philos = malloc(sizeof(t_philo) * data.num_philos);
	if (!obj->philos)
		return (0);
	if (!create_muthreads(obj, data))
		return (0);
	return (1);
}

t_holder	init_holder(char **argv)
{
	t_holder	obj;

	obj.init_err = 1;
	if (parse_args(&obj, argv) != 0)
		return (obj);
	obj.threads = malloc(sizeof(pthread_t) * obj.data.num_philos);
	if (!obj.threads)
	{
		write_err(4);
		return (obj);
	}
	obj.forks = malloc(sizeof(pthread_mutex_t) * obj.data.num_philos);
	if (!obj.forks)
	{
		free(obj.threads);
		write_err(4);
		return (obj);
	}
	obj.init_err = 0;
	return (obj);
}
