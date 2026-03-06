/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 01:48:14 by niklasburch       #+#    #+#             */
/*   Updated: 2025/11/19 15:30:35 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	sem_wait(philo->data->print_sem);
	printf("%llu %d %s\n", get_time() - philo->data->start, philo->id, status);
	sem_post(philo->data->print_sem);
}
