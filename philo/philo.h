/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:22:49 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/19 16:33:28 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	size_t			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*message_lock;
	pthread_mutex_t	*simulation_lock;
	t_data			data;
	struct s_holder	*obj;
}	t_philo;

typedef struct s_holder
{
	pthread_t		*threads;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message_lock;
	pthread_mutex_t	simulation_lock;
	t_philo			*philos;
	t_data			data;
	int				init_err;
	int				is_simulation;
	size_t			start_time;
}	t_holder;

int			ft_putendl_fd(char *s, int fd);
int			is_number(char *arg);
int			write_err(int type);
int			ft_atoi(const char *str);
int			parse_args(t_holder *obj, char **argv);
t_holder	init_holder(char **argv);
void		clean_struct(t_holder *obj);
void		*start_routine(void *obj);
void		*run_monitoring(void *obj);
size_t		get_time(void);
int			is_simulation(t_holder *obj);
void		print_message(t_philo *philo, const char *mes,
				size_t time, int die);
void		set_simulation_end(t_holder *obj);
int			init_philos(t_holder *obj, t_data data);
void		choose_fork_order(t_philo *philo,
				pthread_mutex_t **first_fork, pthread_mutex_t **second_fork);
int			lock_forks(t_philo *philo, size_t *time, size_t start_time);
void		unlock_forks(t_philo *philo);

#endif
