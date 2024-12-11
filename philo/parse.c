/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:34:35 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/11 12:32:04 by msavelie         ###   ########.fr       */
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

static int	check_are_nums_neg(t_philo *philo)
{
	if (philo->philos <= 0
		|| philo->time_to_die <= 0
		|| philo->time_to_eat <= 0
		|| philo->time_to_sleep <= 0)
		return (0);
	return (1);
}

int	parse_args(t_philo *philo, char **argv)
{
	if (!check_are_args_nums(argv))
		return (write_err(2));
	philo->philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (!check_are_nums_neg(philo))
		return (write_err(3));
	if (argv[5])
	{
		philo->meals = ft_atoi(argv[5]);
		if (philo->meals <= 0)
			return (write_err(3));
	}
	else
		philo->meals = -1;
	return (0);
}
