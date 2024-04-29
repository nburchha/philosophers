/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 02:13:10 by niklasburch       #+#    #+#             */
/*   Updated: 2024/04/29 02:15:30 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (1)
	{
		pthread_mutex_lock(philo->right_fork_mutex);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork_mutex);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		philo->last_meal = get_current_time(&philo->data->start_time);
		philo->meal_counter++;
		if (philo->data->meal_count != -1 && philo->meal_counter == (philo->data->meal_count / philo->data->philo_count) && philo->data->meal_count % philo->data->philo_count == 0)
		{
			pthread_mutex_lock(philo->meal_mutex);
			philo->data->philo_dead = philo->philo_id;
			pthread_mutex_unlock(philo->meal_mutex);
			break ;
		}
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork_mutex);
		pthread_mutex_unlock(philo->left_fork_mutex);
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
