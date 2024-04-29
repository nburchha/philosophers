/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 01:48:14 by niklasburch       #+#    #+#             */
/*   Updated: 2024/04/29 02:22:33 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%d %d %s\n", get_current_time(&philo->data->start_time),
		philo->philo_id, status);
	pthread_mutex_unlock(philo->print_mutex);
}
