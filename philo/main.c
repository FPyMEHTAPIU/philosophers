/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:32:45 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/11 17:20:52 by msavelie         ###   ########.fr       */
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
	philo.philo_dead = 0;
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
	free(philo.thread);
	free(philo.forks);
	return (0);
}
