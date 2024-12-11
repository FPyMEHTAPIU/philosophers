/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:17:50 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/11 16:37:52 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_forks(t_philo *philo, int index)
{
	//TODO: lock [0] fork
	// 	if succeed try to lock [1] fork
	// 		if succeed - return
	//		if failed - unlock [0] fork 
}

void	action(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->philo_dead == 0 && (philo->meals != 0))
	{

	}
}
