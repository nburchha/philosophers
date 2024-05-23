/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 02:13:10 by niklasburch       #+#    #+#             */
/*   Updated: 2024/05/23 13:58:03 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;
	int	death;

	philo = (t_philo *)philo_ptr;
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		death = philo->data->death;
		pthread_mutex_unlock(&philo->data->death_mutex);
		if (death != -1)
			break ;
		if (philo->philo_id % 2 == 0) {
			pthread_mutex_lock(philo->right_fork_mutex);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(philo->left_fork_mutex);
		} else {
			pthread_mutex_lock(philo->left_fork_mutex);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(philo->right_fork_mutex);
		}
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		philo->last_meal = get_time();
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->right_fork_mutex);
		pthread_mutex_unlock(philo->left_fork_mutex);
		pthread_mutex_lock(philo->meal_mutex);
		philo->data->meal_counter += 1;
		pthread_mutex_unlock(philo->meal_mutex);
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
