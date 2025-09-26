/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:18:20 by nburchha          #+#    #+#             */
/*   Updated: 2025/09/26 12:27:37 by nburchha         ###   ########.fr       */
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
		pthread_mutex_lock(&data->philos[i].last_meal_sem);
		last_meal = data->philos[i].last_meal;
		pthread_mutex_unlock(&data->philos[i].last_meal_sem);
		if (get_time() - last_meal > (uint64_t)data->time_to_die)
		{
			pthread_mutex_lock(&data->death_sem);
			data->died = data->philos[i].id;
			pthread_mutex_unlock(&data->death_sem);
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
		pthread_mutex_lock(&data->philos[i].meal_sem);
		if (data->philos[i].meal_count >= data->meal_count && \
data->meal_count != -1)
			count++;
		pthread_mutex_unlock(&data->philos[i].meal_sem);
	}
	if (count == data->philo_count)
	{
		pthread_mutex_lock(&data->death_sem);
		data->died = 0;
		pthread_mutex_unlock(&data->death_sem);
	}
}

void	*monitor(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	while (1)
	{
		pthread_mutex_lock(&data->death_sem);
		if (data->died != -1)
			return (pthread_mutex_unlock(&data->death_sem), NULL);
		pthread_mutex_unlock(&data->death_sem);
		check_death(data);
		check_meals(data);
		ft_sleep(0);
	}
	return (NULL);
}
