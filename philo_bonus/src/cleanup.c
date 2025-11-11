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
	if (!data)
		return;
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	close_unlink(&data->forks, "/forks");
	close_unlink(&data->print_sem, "/print");
	close_unlink(&data->death_sem, "/death");
	close_unlink(&data->meal_sem, "/meal");
}
