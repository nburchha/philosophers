/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:48:38 by niklasburch       #+#    #+#             */
/*   Updated: 2024/05/28 15:12:11 by nburchha         ###   ########.fr       */
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
#include <stdint.h>

# define NONE 0
# define FORK_RIGHT 1
# define FORK_LEFT 2
# define DEATH 4


typedef struct s_data t_data;

typedef struct s_philo
{
	int				philo_id;
	int				time_to_eat;
	int				time_to_sleep;
	uint64_t		last_meal;
	pthread_mutex_t	*right_fork_mutex;
	pthread_mutex_t	*left_fork_mutex;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int				meal_count; //optional, if -1 then no meal limit
	pthread_mutex_t	meal_mutex;
	int				meal_counter; // if (meal_counter == (meal_count / philo_count) && meal_count % philo_count == 0) then the philo will stop eating
	int				death; //if a philo died, the philo will set this to his id
	uint64_t		start; // TODO: change this to uint64_t and  use (start - get_time)
	t_philo			*philos;
	pthread_t		monitor_thread;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
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