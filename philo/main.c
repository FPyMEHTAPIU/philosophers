/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:32:45 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/11 12:34:26 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	init_philo(char **argv)
{
	t_philo	philo;

	philo.init_err = 1;
	if (parse_args(&philo, argv) != 0)
		return (philo);
	philo.thread = malloc(sizeof(pthread_t) * philo.philos);
	if (!philo.thread)
	{
		write_err(4);
		return (philo);
	}
	philo.forks = malloc(sizeof(pthread_mutex_t) * philo.philos);
	if (!philo.forks)
	{
		free(philo.thread);
		write_err(4);
		return (philo);
	}
	philo.init_err = 0;
	return (philo);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || argc > 6)
		return (write_err(1));
	philo = init_philo(argv);
	if (philo.init_err == 1)
		return (1);
	printf("philos: %d\n", philo.philos);
	printf("time_to_die: %d\n", philo.time_to_die);
	printf("time_to_eat: %d\n", philo.time_to_eat);
	printf("time_to_sleep: %d\n", philo.time_to_sleep);
	printf("meals: %d\n", philo.meals);
	free(philo.thread);
	free(philo.forks);
	return (0);
}
