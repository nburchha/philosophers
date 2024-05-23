/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:18:20 by nburchha          #+#    #+#             */
/*   Updated: 2024/05/23 13:45:32 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (get_time() - data->philos[i].last_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("%llu %d died\n", get_time() - data->start, i + 1);
			pthread_mutex_unlock(&data->print_mutex);
			data->death = data->philos[i].philo_id;
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
		if (data->death != -1)
			return (NULL);
		check_philos(data);
		// ft_usleep(10);
	}
	return (NULL);
}
