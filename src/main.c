/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:51:31 by niklasburch       #+#    #+#             */
/*   Updated: 2024/05/23 13:13:12 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!init_data(&data, argc, argv))
		return (printf("Error: invalid arguments\n"), 1);
	if (!init_philos(&data))
		return (cleanup(&data), printf("Error initializing philos\n"), 1);
	pthread_create(&data.monitor_thread, NULL, monitor, &data);
	pthread_detach(data.monitor_thread);
	for (int i = 0; i < data.philo_count; i++)
	{
		pthread_create(&data.philos[i].thread, NULL, philo_routine, &data.philos[i]);
		pthread_detach(data.philos[i].thread);
	}
	
	while (1)
	{
		if (data.death != -1)
			break ;
	}
	cleanup(&data);
	return (0);
}