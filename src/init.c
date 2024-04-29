/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:55:14 by niklasburch       #+#    #+#             */
/*   Updated: 2024/04/29 03:29:44 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	null_mutexes(t_philo *philo)
{
	philo->print_mutex = NULL;
	philo->right_fork_mutex = NULL;
	philo->meal_mutex = NULL;
}

static bool	init_mutexes(t_philo *philo)
{
	philo->meal_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philo->meal_mutex)
		return (false);
	pthread_mutex_init(philo->meal_mutex, NULL);
	philo->right_fork_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philo->right_fork_mutex)
		return (false);
	pthread_mutex_init(philo->right_fork_mutex, NULL);
	return (true);
}

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
		philos[i].philo_id = i + 1;
		philos[i].last_meal = data->start_time;
		null_mutexes(&philos[i]);
		if (!init_mutexes(&philos[i]))
			return (false);
		if (i != 0)
			philos[i].left_fork_mutex = philos[i - 1].right_fork_mutex;
		if (i == data->philo_count - 1)
			philos[0].left_fork_mutex = philos[i].left_fork_mutex;
		philos[i].print_mutex = &data->print_mutex;
		philos[i].data = data;
		i++;
	}
	data->philos = philos;
	return (true);
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
	data->meal_counter = 0;
	data->philo_dead = -1;
	gettimeofday(&data->start_time, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	return (true);
}
