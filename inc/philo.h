/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:48:38 by niklasburch       #+#    #+#             */
/*   Updated: 2024/04/29 03:03:39 by niklasburch      ###   ########.fr       */
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

typedef struct s_data t_data;

typedef struct s_philo
{
	int				philo_id;
	pthread_mutex_t	*right_fork_mutex;
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*meal_mutex; //every time the philo ate, it will lock this mutex and increase the meal_counter, if (meal_counter == (meal_count / philo_count) && meal_count % philo_count == 0) then the philo will stop eating
	t_data			*data;
	struct timeval	last_meal;
	pthread_t		thread;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count; //optional, if -1 then no meal limit
	int				meal_counter; // if (meal_counter == (meal_count / philo_count) && meal_count % philo_count == 0) then the philo will stop eating
	int				philo_dead; //if a philo died, the philo will set this to his id
	struct timeval	start_time;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
}	t_data;

void	*philo_routine(void *philo_ptr);
bool	init_data(t_data *data, int argc, char **argv);
bool	init_philos(t_data *data);
void	cleanup(t_data *data);
void	print_status(t_philo *philo, char *status);
int		get_current_time(struct timeval *start_time);
int		ft_atoi(const char *str);

#endif