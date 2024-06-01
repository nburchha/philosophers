/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:55:14 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/01 02:55:31 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].last_meal = data->start;
		philos[i].time_to_eat = data->time_to_eat;
		philos[i].time_to_sleep = data->time_to_sleep;
		philos[i].meal_count = 0;
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		pthread_mutex_init(&philos[i].last_meal_mutex, NULL);
		(&(philos[i]))->left_fork_mutex = &(data->forks[i]);
		(&(philos[i]))->right_fork_mutex = &(data->forks[(i + 1) \
		% data->philo_count]);
		philos[i].data = data;
		i++;
	}
	data->philos = philos;
	return (true);
}

void	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_init(&data->forks[i], NULL);
}

bool	init_data(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (false);
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meal_count = ft_atoi(argv[5]);
	else
		data->meal_count = -1;
	if (data->philo_count < 1 || data->philo_count > 200 || \
		data->time_to_die < 0 || data->time_to_eat < 0 || \
		data->time_to_sleep < 0 || (argc == 6 && data->meal_count < 0))
		return (printf("All input values must be positive and number of \
				philosophers must be between 1 and 200!\n"), false);
	data->died = -1;
	data->start = get_time();
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (false);
	init_mutexes(data);
	return (true);
}
