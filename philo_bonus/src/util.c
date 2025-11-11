/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:59:40 by niklasburch       #+#    #+#             */
/*   Updated: 2025/09/26 12:30:39 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	die(t_philo *philo, int to_unlock)
{
	int	current_flag;

	if (!philo || !philo->data)
		return;
	while (to_unlock)
	{
		current_flag = to_unlock & -to_unlock;
		if (current_flag == SEM_FORKS)
			close_unlink(&philo->data->forks, "/forks");
		else if (current_flag == SEM_PRINT)
			close_unlink(&philo->data->print_sem, "/print");
		else if (current_flag == SEM_DEATH)
			close_unlink(&philo->data->death_sem, "/death");
		else if (current_flag == SEM_MEAL)
			close_unlink(&philo->data->meal_sem, "/meal");
		to_unlock &= ~current_flag;
	}
}

uint64_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	result;

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
		if (result > INT_MAX)
			return (INT_MIN);
		i++;
	}
	return (result * sign);
}

void	ft_sleep(uint64_t time)
{
	uint64_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

void	close_unlink(sem_t **s, const char *name)
{
	if (*s && *s != SEM_FAILED) sem_close(*s);
	sem_unlink(name);
	*s = NULL;
}
