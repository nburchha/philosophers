/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:18:20 by nburchha          #+#    #+#             */
/*   Updated: 2025/11/19 15:30:52 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		if (sem_wait(philo->last_meal_sem) != 0)
			printf("Error waiting for last_meal_sem in monitor\n");
		if (get_time() - philo->last_meal > (uint64_t)philo->data->time_to_die)
		{
			sem_wait(philo->data->print_sem);
			printf("%llu %d died\n", (unsigned long long)(get_time() - philo->data->start),
				philo->id);
			sem_post(philo->data->death_sem);
			exit(1);
		}
		if (sem_post(philo->last_meal_sem) != 0)
			printf("Error posting last_meal_sem in monitor\n");
		ft_sleep(1);
	}
	return (NULL);
}
