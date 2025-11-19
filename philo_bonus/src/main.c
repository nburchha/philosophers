/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:51:31 by niklasburch       #+#    #+#             */
/*   Updated: 2025/11/10 17:33:01 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitor_meals(void *param)
{
	t_data	*data;
	int		i;

	data = (t_data *)param;
	i = 0;
	while (i < data->philo_count)
	{
		sem_wait(data->meal_sem);
		i++;
	}
	sem_post(data->death_sem);
	return (NULL);
}

bool	start_processes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
			return (printf("Error forking\n"), false);
		if (data->philos[i].pid == 0)
		{
			philo_routine(&data->philos[i]);
			exit(0);
		}
	}
	if (data->meal_count != -1)
		if (pthread_create(&data->monitor_thread, NULL, monitor_meals, data))
			return (printf("Error creating meal monitor thread\n"), false);
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
	if (!start_processes(&data))
		return (cleanup(&data), 1);
	sem_wait(data.death_sem);
	i = -1;
	while (++i < data.philo_count)
		kill(data.philos[i].pid, SIGKILL);
	cleanup(&data);
	return (0);
}
