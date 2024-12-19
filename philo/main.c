/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:32:45 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/19 10:32:12 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_holder	obj;

	if (argc < 5 || argc > 6)
		return (write_err(1));
	obj = init_holder(argv);
	if (obj.init_err == 1)
		return (1);
	clean_struct(&obj);
	return (0);
}
