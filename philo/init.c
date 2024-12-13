/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:36:14 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/13 17:08:07 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_holder *obj, t_data data)
{
	int	i;

	i = 0;
	while (i < data.num_philos)
	{
		obj->philos[i].data = data;
		obj->philos[i].thread = &obj->threads[i];
		obj->philos[i].left_fork = &obj->forks[i];
		obj->philos[i].right_fork = &obj->forks[(i + 1) % data.num_philos];
		obj->philos[i].id = i + 1;
		obj->philos[i].is_dead = 0;
		obj->philos[i].meals_eaten = 0;
		obj->philos[i].is_simulation = 1;
		pthread_mutex_init(&obj->philos[i].meal_lock, NULL);
		pthread_mutex_init(&obj->philos[i].message_lock, NULL);
		pthread_mutex_init(&obj->philos[i].simulation_lock, NULL);
		i++;
	}
}

static int	create_muthreads(t_holder *obj, t_data data)
{
	int	i;

	//printf("philos: %d\n", data.num_philos);
	//printf("time_to_die: %d\n", data.time_to_die);
	//printf("time_to_eat: %d\n", data.time_to_eat);
	//printf("time_to_sleep: %d\n", data.time_to_sleep);
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
	assign_forks(obj, data);
	i = 0;
	while (i < data.num_philos)
	{
		if (pthread_create(&obj->threads[i], NULL, start_routine, (void *)&obj->philos[i]) != 0)
		{
			while (i--)
				pthread_join(obj->threads[i], NULL);
			return (0);
		}
		//printf("thread %d created!\n", i);
		i++;
	}
	return (1);
}

static int	init_philos(t_holder *obj, t_data data)
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
	if (!init_philos(&obj, obj.data))
		clean_struct(&obj);
	else
		obj.init_err = 0;
	obj.philo_dead = 0;
	return (obj);
}
