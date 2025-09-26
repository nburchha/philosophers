/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 01:42:42 by niklasburch       #+#    #+#             */
/*   Updated: 2025/09/26 12:27:36 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	cleanup(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_sem);
		pthread_mutex_destroy(&data->philos[i].last_meal_sem);
	}
	free(data->philos);
	free(data->forks);
	pthread_mutex_destroy(&data->print_sem);
	pthread_mutex_destroy(&data->death_sem);
	pthread_mutex_destroy(&data->meal_sem);
}
