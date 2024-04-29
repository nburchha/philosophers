/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:51:31 by niklasburch       #+#    #+#             */
/*   Updated: 2024/04/29 02:20:38 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"



void	print_data(t_data *data)
{
	printf("philo_count: %d\n", data->philo_count);
	printf("time_to_die: %d\n", data->time_to_die);
	printf("time_to_eat: %d\n", data->time_to_eat);
	printf("time_to_sleep: %d\n", data->time_to_sleep);
	printf("meal_count: %d\n", data->meal_count);
	printf("meal_counter: %d\n", data->meal_counter);
	printf("start_time: %ld\n", data->start_time.tv_sec);
	for (int i = 0; i < data->philo_count; i++)
	{
		printf("philo_id: %d\n", data->philos[i].philo_id);
		printf("meal_counter: %d\n", data->philos[i].meal_counter);
		printf("last_meal: %d\n", get_current_time(&data->philos[i].last_meal));
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!init_data(&data, argc, argv))
		return (printf("Error: invalid arguments\n"), 1);
	if (!init_philos(&data))
		return (cleanup(&data), printf("Error initializing philos\n"), 1);
	print_data(&data);
	cleanup(&data);
	return (0);
}
