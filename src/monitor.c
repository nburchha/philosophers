/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:18:20 by nburchha          #+#    #+#             */
/*   Updated: 2024/05/31 14:41:16 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_philos(t_data *data)
{
	int	i;
	uint64_t	last_meal;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_lock(&data->lock);
		last_meal = data->philos[i].last_meal;
		pthread_mutex_unlock(&data->lock);
		if (get_time() - last_meal > (uint64_t)data->time_to_die)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->death = data->philos[i].philo_id;
			pthread_mutex_unlock(&data->death_mutex);
			print_status(&data->philos[i], "died");
			return ;
		}
	}
}

void	*monitor(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	while (1)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->death != -1)
			return (pthread_mutex_unlock(&data->death_mutex), NULL);
		pthread_mutex_unlock(&data->death_mutex);
		check_philos(data);
		pthread_mutex_lock(&data->meal_mutex);
		if (data->meal_count != -1 && data->meal_counter >= data->meal_count * data->philo_count)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->death = 0;
			pthread_mutex_unlock(&data->death_mutex);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		ft_usleep(0);
	}
	return (NULL);
}
