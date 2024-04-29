/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 01:42:42 by niklasburch       #+#    #+#             */
/*   Updated: 2024/04/29 02:10:25 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

	void	cleanup(t_data *data)
	{
		int	i;

		i = -1;
		while (++i < data->philo_count)
		{
			if (data->philos[i].meal_mutex)
				pthread_mutex_destroy(data->philos[i].meal_mutex);
			if (data->philos[i].right_fork_mutex)
				pthread_mutex_destroy(data->philos[i].right_fork_mutex);
			if (data->philos[i].left_fork_mutex)
				pthread_mutex_destroy(data->philos[i].left_fork_mutex);
		}
		free(data->philos);
}
