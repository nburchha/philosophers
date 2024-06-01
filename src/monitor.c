/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:18:20 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/01 11:49:36 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_death(t_data *data)
{
	int			i;
	uint64_t	last_meal;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_lock(&data->philos[i].last_meal_mutex);
		last_meal = data->philos[i].last_meal;
		pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
		if (get_time() - last_meal > (uint64_t)data->time_to_die)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->died = data->philos[i].id;
			pthread_mutex_unlock(&data->death_mutex);
			print_status(&data->philos[i], "died");
			return ;
		}
	}
}

void	check_meals(t_data *data)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < data->philo_count)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].meal_count >= data->meal_count && \
			data->meal_count != -1)
			count++;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
	}
	if (count == data->philo_count)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->died = 0;
		pthread_mutex_unlock(&data->death_mutex);
	}
}

void	*monitor(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	while (1)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->died != -1)
			return (pthread_mutex_unlock(&data->death_mutex), NULL);
		pthread_mutex_unlock(&data->death_mutex);
		check_death(data);
		check_meals(data);
		ft_sleep(0);
	}
	return (NULL);
}
