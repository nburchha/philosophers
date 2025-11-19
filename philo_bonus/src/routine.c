/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 02:13:10 by niklasburch       #+#    #+#             */
/*   Updated: 2025/11/11 10:40:24 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	sem_wait(philo->last_meal_sem);
	philo->last_meal = get_time();
	sem_post(philo->last_meal_sem);
	ft_sleep(philo->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo		*philo;
	pthread_t	monitor_thread;

	philo = (t_philo *)philo_ptr;
	if (pthread_create(&monitor_thread, NULL, monitor, philo))
		return (NULL);
	pthread_detach(monitor_thread);
	if (philo->id % 2 != 0)
		ft_sleep(philo->time_to_eat / 2);
	while (1)
	{
		eat(philo);
		philo->meal_count += 1;
		if (philo->meal_count == philo->data->meal_count)
		{
			sem_post(philo->data->meal_sem);
			return (NULL);
		}
		print_status(philo, "is sleeping");
		ft_sleep(philo->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
