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

#include "philo.h"

void	cleanup(t_data *data)
{
	int		i;
	char	name[30];

	if (!data)
		return ;
	if (data->philos)
	{
		i = 0;
		while (i < data->philo_count)
		{
			create_sem_name(name, data->philos[i].id);
			close_unlink(&data->philos[i].last_meal_sem, name);
			i++;
		}
		free(data->philos);
		data->philos = NULL;
	}
	close_unlink(&data->forks, "/forks");
	close_unlink(&data->print_sem, "/print");
	close_unlink(&data->death_sem, "/death");
	close_unlink(&data->meal_sem, "/meal");
}
