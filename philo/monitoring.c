/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:25:19 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/14 17:18:43 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_simulation_end(t_holder *obj)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&obj->simulation_lock);
	obj->is_simulation = 0;
	pthread_mutex_unlock(&obj->simulation_lock);
	clean_struct(obj);
}

static int	check_all_alive(t_holder *obj)
{
	int		i;
	size_t	time;

	i = 0;
	while (i < obj->data.num_philos)
	{
		pthread_mutex_lock(&obj->philos[i].meal_lock);
		time = get_time();
		if (!is_simulation(obj) ||
			time - obj->philos[i].last_meal_time >= (size_t) obj->data.time_to_die)
		{
			pthread_mutex_unlock(&obj->philos[i].meal_lock);
			print_message(&obj->philos[i], "died", time - obj->start_time, 1);
			return (0);
		}
		pthread_mutex_unlock(&obj->philos[i].meal_lock);
		i++;
	}
	return (1);
}

static int	check_meals_completed(t_holder *obj, t_data data)
{
	int		i;
	size_t	time;

	if (data.meals == -1)
		return (0);
	i = 0;
	while (i < obj->data.num_philos)
	{
		pthread_mutex_lock(&obj->philos[i].meal_lock);
		time = get_time();
		if (!is_simulation(obj))
		{
			pthread_mutex_unlock(&obj->philos[i].meal_lock);
			print_message(&obj->philos[i], "died", time - obj->start_time, 1);
			return (1);
		}
		if (obj->philos[i].meals_eaten < data.meals)
		{
			pthread_mutex_unlock(&obj->philos[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&obj->philos[i].meal_lock);
		i++;
	}
	printf("Harry you are a wizard!\n");
	return (1);
}

void	run_monitoring(t_holder *obj)
{
	int		meals_completed;

	while (is_simulation(obj) != 0)
	{
		meals_completed = check_meals_completed(obj, obj->data);
		if (meals_completed == 1)
		{
			break ;
		}
		if (check_all_alive(obj) == 0)
		{
			break ;
		}
		usleep(100);
	}
}
