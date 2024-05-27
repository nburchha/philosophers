/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:59:40 by niklasburch       #+#    #+#             */
/*   Updated: 2024/05/27 17:18:17 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	die(t_philo *philo, int to_unlock)
{
	// pthread_mutex_lock(&philo->data->print_mutex);
	if (to_unlock & FORK_RIGHT && printf("right fork unlocked\n"))
		pthread_mutex_unlock(philo->right_fork_mutex);
	if (to_unlock & FORK_LEFT && printf("left fork unlocked\n"))
		pthread_mutex_unlock(philo->left_fork_mutex);
	if (to_unlock & DEATH && printf("philo death mutex unlocked\n"))
		pthread_mutex_unlock(&philo->data->death_mutex);
	// pthread_mutex_unlock(&philo->data->print_mutex);
}

uint64_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

void	ft_usleep(uint64_t time)
{
	uint64_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}