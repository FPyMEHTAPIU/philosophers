/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:34:35 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/14 17:05:17 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_are_args_nums(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_number(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_are_nums_neg(t_holder *obj)
{
	if (obj->data.num_philos <= 0
		|| obj->data.time_to_die <= 0
		|| obj->data.time_to_eat <= 0
		|| obj->data.time_to_sleep <= 0)
		return (0);
	return (1);
}

int	parse_args(t_holder *obj, char **argv)
{
	if (!check_are_args_nums(argv))
		return (write_err(2));
	obj->data.num_philos = ft_atoi(argv[1]);
	if (obj->data.num_philos == 1)
	{
		printf("0 1 died\n");
		return (1);
	}
	obj->data.time_to_die = ft_atoi(argv[2]);
	obj->data.time_to_eat = ft_atoi(argv[3]);
	obj->data.time_to_sleep = ft_atoi(argv[4]);
	if (!check_are_nums_neg(obj))
		return (write_err(3));
	if (argv[5])
	{
		obj->data.meals = ft_atoi(argv[5]);
		if (obj->data.meals <= 0)
			return (write_err(3));
	}
	else
		obj->data.meals = -1;
	obj->is_simulation = 1;
	return (0);
}
