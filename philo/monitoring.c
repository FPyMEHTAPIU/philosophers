/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:25:19 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/14 13:42:37 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_simulation_end(t_holder *obj)
{
	int	i;

	i = 0;
	while (i < obj->data.num_philos)
	{
		pthread_mutex_lock(&obj->simulation_lock);
		obj->philos[i].is_simulation = 0;
		pthread_mutex_unlock(&obj->simulation_lock);
		i++;
	}
	clean_struct(obj);
}

static int	check_all_alive(t_holder *obj/*, size_t start_time*/)
{
	int		i;
	size_t	time;

	i = 0;
	time = get_time();
	while (i < obj->data.num_philos)
	{
		pthread_mutex_lock(&obj->philos[i].meal_lock);
		if (!is_simulation(&obj->philos[i]) || obj->philos[i].is_dead == 1)
		{
			pthread_mutex_lock(obj->philos[i].message_lock);
			set_simulation_end(obj);
			//pthread_mutex_unlock(obj->philos[i].message_lock);
			//print_message(&obj->philos[i], "died in monitoring", time - start_time, 1);
			//pthread_mutex_unlock(&obj->philos[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&obj->philos[i].meal_lock);
		i++;
	}
	return (1);
}

static int	check_meals_completed(t_holder *obj, t_data data)
{
	int	i;

	if (data.meals == -1)
		return (0);
	i = 0;
	while (i < obj->data.num_philos)
	{
		pthread_mutex_lock(&obj->philos[i].meal_lock);
		if (!is_simulation(&obj->philos[i]) || obj->philos[i].meals_eaten < data.meals)
		{
			pthread_mutex_unlock(&obj->philos[i].meal_lock);
			pthread_mutex_lock(obj->philos[i].message_lock);
			set_simulation_end(obj);
			//pthread_mutex_unlock(obj->philos[i].message_lock);
			return (0);
		}
		pthread_mutex_unlock(&obj->philos[i].meal_lock);
		i++;
	}
	return (1);
}

void	run_monitoring(t_holder *obj)
{
	size_t	start_time;

	start_time = get_time();
	while (is_simulation(obj->philos) != 0)
	{
		if (!is_simulation(obj->philos) || check_all_alive(obj/*, start_time*/) == 0 || check_meals_completed(obj, obj->data) == 1)
			break;
		usleep(30);
	}
}
