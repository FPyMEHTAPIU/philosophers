/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:22:49 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/13 12:51:13 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_data
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals;
}	t_data;

typedef struct	s_philo
{
	int				id;
	int				meals_eaten;
	size_t			last_meal_time;
	int				is_dead;
	pthread_t		*thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			data;
}	t_philo;

typedef struct	s_holder
{
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	t_data			data;
	int				init_err;
	int				philo_dead;
}	t_holder;

int			ft_putendl_fd(char *s, int fd);
int			is_number(char *arg);
int			write_err(int type);
int			ft_atoi(const char *str);
int			parse_args(t_holder *obj, char **argv);
void		action(t_holder *obj);
t_holder	init_holder(char **argv);
void		clean_struct(t_holder *obj);
void		*start_routine(void *obj);

#endif