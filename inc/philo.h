/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:48:38 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/01 02:54:23 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdint.h>

# define NONE 0
# define FORK_RIGHT 1
# define FORK_LEFT 2
# define DEATH 4

typedef struct s_data	t_data;
typedef struct s_philo
{
	int				id;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	uint64_t		last_meal;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	*right_fork_mutex;
	pthread_mutex_t	*left_fork_mutex;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	pthread_mutex_t	meal_mutex;
	int				died;
	uint64_t		start;
	t_philo			*philos;
	pthread_t		monitor_thread;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
}	t_data;

void		*philo_routine(void *philo_ptr);
void		*monitor(void *param);
bool		init_data(t_data *data, int argc, char **argv);
bool		init_philos(t_data *data);
void		cleanup(t_data *data);
void		print_status(t_philo *philo, char *status);
uint64_t	get_time(void);
int			ft_atoi(const char *str);
void		ft_usleep(uint64_t time);
void		die(t_philo *philo, int to_unlock);

#endif