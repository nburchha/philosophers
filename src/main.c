/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:51:31 by niklasburch       #+#    #+#             */
/*   Updated: 2024/05/23 16:02:12 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


void	threads(t_data *data)
{
	int	i;

	pthread_create(&data->monitor_thread, NULL, monitor, data);
	pthread_detach(data->monitor_thread);
	i = -1;
	while (++i < data->philo_count)
	{
		pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]);
		pthread_detach(data->philos[i].thread);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		flag;

	if (!init_data(&data, argc, argv))
		return (printf("Error: invalid arguments\n"), 1);
	if (!init_philos(&data))
		return (cleanup(&data), printf("Error initializing philos\n"), 1);
	threads(&data);
	while (1)
	{
		pthread_mutex_lock(&data.death_mutex);
		flag = data.death;
		pthread_mutex_unlock(&data.death_mutex);
		if (flag != -1)
			break ;
	}
	cleanup(&data);
	return (0);
}
