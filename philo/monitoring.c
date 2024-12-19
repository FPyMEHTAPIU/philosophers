/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:25:19 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/19 12:21:01 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_simulation_end(t_holder *obj)
{
	pthread_mutex_lock(&obj->simulation_lock);
	obj->is_simulation = 0;
	pthread_mutex_unlock(&obj->simulation_lock);
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
		if (!is_simulation(obj))
			return (0);
		if (obj->philos[i].last_meal_time == 0)
			return (1);
		if (time - obj->philos[i].last_meal_time >= (size_t) obj->data.time_to_die)
		{
			print_message(&obj->philos[i], "died", time - obj->start_time, 1);
			set_simulation_end(obj);
			pthread_mutex_unlock(&obj->philos[i].meal_lock);
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

	if (data.meals == -1)
		return (0);
	i = 0;
	while (i < obj->data.num_philos)
	{
		pthread_mutex_lock(&obj->philos[i].meal_lock);
		if (obj->philos[i].meals_eaten < data.meals)
		{
			pthread_mutex_unlock(&obj->philos[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&obj->philos[i].meal_lock);
		i++;
	}
	set_simulation_end(obj);
	return (1);
}

void	*run_monitoring(void *obj)
{
	int		meals_completed;
	t_holder	*temp;

	temp = (t_holder *)obj;
	while (is_simulation(temp) != 0)
	{
		meals_completed = check_meals_completed(temp, temp->data);
		if (meals_completed == 1)
			break ;
		if (check_all_alive(temp) == 0)
			break ;
		usleep(1000);
	}
	return (NULL);
}
