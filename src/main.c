/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:51:31 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/01 14:25:54 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	threads(t_data *data)
{
	int	i;

	if (pthread_create(&data->monitor_thread, NULL, monitor, data))
		return (printf("Error creating monitor thread\n"), cleanup(data), \
		false);
	i = -1;
	while (++i < data->philo_count)
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, \
			&data->philos[i]))
			return (printf("Error creating philo thread\n"), cleanup(data), \
			false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!init_data(&data, argc, argv))
		return (printf("Error: invalid arguments\n"), 1);
	if (!init_philos(&data))
		return (cleanup(&data), printf("Error initializing philos\n"), 1);
	if (data.philo_count == 1)
	{
		printf("0 1 has taken a fork\n");
		ft_sleep(data.time_to_die);
		printf("%d 1 died\n", data.time_to_die);
		return (cleanup(&data), 0);
	}
	if (!threads(&data))
		return (1);
	i = 0;
	while (i < data.philo_count)
		pthread_join(data.philos[i++].thread, NULL);
	pthread_join(data.monitor_thread, NULL);
	cleanup(&data);
	return (0);
}
