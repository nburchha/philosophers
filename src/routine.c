/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 02:13:10 by niklasburch       #+#    #+#             */
/*   Updated: 2024/05/31 15:34:14 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork_mutex);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->death != -1)
		return (die(philo, DEATH | FORK_LEFT), (void)0);
	pthread_mutex_unlock(&philo->data->death_mutex);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->death != -1)
		return (die(philo, DEATH | FORK_LEFT), (void)0);
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(philo->right_fork_mutex);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->death != -1)
		return (die(philo, DEATH | FORK_RIGHT | FORK_LEFT), (void)0);
	pthread_mutex_unlock(&philo->data->death_mutex);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork_mutex);
	pthread_mutex_unlock(philo->right_fork_mutex);
}

/*mutex integer is used to now which mutex needs to be unlocked in case of death midst routine*/

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	// printf("philo id: %d\nforks:\nright: %p, left: %p\n\n", philo->philo_id, philo->right_fork_mutex, philo->left_fork_mutex);
	if (philo->philo_id % 2 != 0)
		ft_usleep(philo->time_to_sleep / 2);
	while (1)
	{
		eat(philo);
		pthread_mutex_lock(&philo->data->meal_mutex);
		philo->data->meal_counter += 1;
		pthread_mutex_unlock(&philo->data->meal_mutex);
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->death != -1)
			return (die(philo, DEATH), NULL);
		pthread_mutex_unlock(&philo->data->death_mutex);
		print_status(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->death != -1)
			return (die(philo, DEATH), NULL);
		pthread_mutex_unlock(&philo->data->death_mutex);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
