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

#include "philo.h"

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
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
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
	if (*s && *s != SEM_FAILED)
		sem_close(*s);
	sem_unlink(name);
	*s = NULL;
}

void	create_sem_name(char *buffer, int id)
{
	int	i;
	int	temp;
	int	len;

	i = -1;
	while ("/philo_lm_"[++i])
		buffer[i] = "/philo_lm_"[i];
	temp = id;
	len = (id == 0);
	while (temp > 0 && ++len)
		temp /= 10;
	buffer[i + len] = '\0';
	while (len > 0)
	{
		buffer[i + len - 1] = (id % 10) + '0';
		id /= 10;
		len--;
	}
}
