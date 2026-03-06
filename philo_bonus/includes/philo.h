/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:48:38 by niklasburch       #+#    #+#             */
/*   Updated: 2025/11/11 10:41:42 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define NONE 0
# define SEM_FORKS 1
# define SEM_PRINT 2
# define SEM_DEATH 4
# define SEM_MEAL 8

typedef struct s_data	t_data;
typedef struct s_philo
{
	int					id;
	int					time_to_eat;
	int					time_to_sleep;
	int					meal_count;
	uint64_t			last_meal;
	sem_t				*meal_sem;
	sem_t				*last_meal_sem;
	sem_t				*forks;
	pthread_t			thread;
	pid_t				pid;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meal_count;
	sem_t				*meal_sem;
	int					died;
	uint64_t			start;
	t_philo				*philos;
	pthread_t			monitor_thread;
	sem_t				*death_sem;
	sem_t				*print_sem;
	sem_t				*forks;
}						t_data;

void					*philo_routine(void *philo_ptr);
void					*monitor(void *param);
bool					init_data(t_data *data, int argc, char **argv);
bool					init_philos(t_data *data);
void					cleanup(t_data *data);
void					print_status(t_philo *philo, char *status);
uint64_t				get_time(void);
int						ft_atoi(const char *str);
void					ft_sleep(uint64_t time);
void					die(t_philo *philo, int to_unlock);
void					close_unlink(sem_t **s, const char *name);
void					create_sem_name(char *buffer, int id);

#endif