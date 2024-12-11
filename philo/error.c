/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:49:44 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/11 12:34:34 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_err(int type)
{
	if (type == 1)
		ft_putendl_fd("Incorrect number of arguments! \
provide 4 or 5 arguments!", 2);
	else if (type == 2)
		ft_putendl_fd("Not all arguments are positive numbers!", 2);
	else if (type == 3)
		ft_putendl_fd("Invalid number", 2);
	else if (type == 4)
		ft_putendl_fd("Malloc error", 2);
	return (1);
}
