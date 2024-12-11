/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:49:44 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/11 11:56:42 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_err(int type)
{
	if (type == 1)
		ft_putendl_fd("Incorrect number of arguments\
provide at least 4 arguments!", 2);
	else if (type == 2)
		ft_putendl_fd("Not all arguments are numbers!", 2);
	return (1);
}
