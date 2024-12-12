/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:22:49 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/12 12:42:30 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_holder
{
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	int				init_err;
	int				philo_dead;
}	t_holder;

typedef struct	s_philo
{
	int				id;
	int				meals_eaten;
	int				is_dead;
	pthread_t		*thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

int			ft_putendl_fd(char *s, int fd);
int			is_number(char *arg);
int			write_err(int type);
int			ft_atoi(const char *str);
int			parse_args(t_holder *obj, char **argv);
void		action(t_holder *obj);
t_holder	init_holder(char **argv);

#endif