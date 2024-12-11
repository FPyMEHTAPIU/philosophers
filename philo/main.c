/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:32:45 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/11 12:02:00 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*init_philo(char **argv)
{
	t_philo	philo;

	if (parse_args(&philo, argv))
		return (NULL);

	return (&philo);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5)
		return (write_err(1));
	if (!init_philo)
		return (1);
	return (0);
}
