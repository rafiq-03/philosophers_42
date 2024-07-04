/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:48:40 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/06/23 17:50:43 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;
	long	before;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		before = res;
		res = (res * 10) + (*str - 48);
		if (res / 10 != before && sign == -1)
			return (0);
		else if (res / 10 != before && sign == 1)
			return (-1);
		str++;
	}
	return (res * sign);
}

void	ft_sleep(long ms)
{
	long	start;
	long	cur;

	start = ft_get_time();
	while (1)
	{
		usleep(100);
		cur = ft_get_time();
		if (cur - ms >= start)
			return ;
	}
}

long	ft_get_time(void)
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return (cur.tv_sec * 1000 + cur.tv_usec / 1000);
}

void	print(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->die_lock);
	if (philo->data->is_die > 0)
	{
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->data->die_lock);
		return ;
	}
	printf("\x1B[34m%ld  \x1B[0m%d  %s\n", ft_get_time()
		- philo->data->start_time, philo->id, s);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_unlock(&philo->data->die_lock);
}

void	death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->die_lock);
	philo->data->is_die = philo->id + 1;
	pthread_mutex_unlock(&philo->data->die_lock);
	pthread_mutex_lock(&philo->data->print);
	printf("\x1B[31m%ld  %d  died\x1B[0m\n", ft_get_time()
		- philo->data->start_time, philo->data->is_die);
	pthread_mutex_unlock(&philo->data->print);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}
