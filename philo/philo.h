/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:22:49 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/11 11:57:15 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_philo
{
	pthread_t		*thread;
	pthread_mutex_t	*forks;
	int				philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
}	t_philo;

void	ft_putendl_fd(char *s, int fd);
int		is_number(char *arg);
int		write_err(int type);
int		ft_atoi(const char *str);
int		parse_args(t_philo *philo, char **argv);

#endif