/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:55:14 by niklasburch       #+#    #+#             */
/*   Updated: 2025/11/10 17:28:37 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	init_philo_sems(t_philo *philo)
{
	char	name[30];

	create_sem_name(name, philo->id);
	sem_unlink(name);
	philo->last_meal_sem = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->last_meal_sem == SEM_FAILED)
		return (false);
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
		philos[i].id = i + 1;
		philos[i].last_meal = data->start;
		philos[i].time_to_eat = data->time_to_eat;
		philos[i].time_to_sleep = data->time_to_sleep;
		philos[i].meal_count = 0;
		philos[i].data = data;
		if (!init_philo_sems(&philos[i]))
			return (false);
		i++;
	}
	data->philos = philos;
	return (true);
}

static bool	init_sync_sems(t_data *d)
{
	d->print_sem = d->death_sem = d->meal_sem = SEM_FAILED;
	sem_unlink("/print");
	sem_unlink("/death");
	sem_unlink("/meal");
	sem_unlink("/forks");
	d->print_sem = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	d->death_sem = sem_open("/death", O_CREAT | O_EXCL, 0644, 0);
	d->meal_sem = sem_open("/meal", O_CREAT | O_EXCL, 0644, 0);
	if (d->print_sem == SEM_FAILED || d->death_sem == SEM_FAILED || d->meal_sem == SEM_FAILED)
		return (false);
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
	if (data->philo_count < 1 || data->philo_count > 200
		|| data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1 || (argc == 6 && data->meal_count < 0))
		return (false);
	data->died = -1;
	data->start = get_time();
	data->forks = sem_open("/forks", O_CREAT, 0644, data->philo_count);
	if (data->forks == SEM_FAILED)
		return (false);
	return (init_sync_sems(data));
}
