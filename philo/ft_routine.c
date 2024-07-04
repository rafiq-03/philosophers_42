/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:59:54 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/06/23 16:26:10 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	if (philo->data->philo_nb == 1)
		ft_sleep(philo->data->time2die);
	if (philo->id % 2 == 0)
		sleeping(philo);
	while (1)
	{
		pthread_mutex_lock(&philo->data->eat_times_lock);
		if (!philo->data->eat_times)
			return (pthread_mutex_unlock(&philo->data->eat_times_lock), NULL);
		pthread_mutex_unlock(&philo->data->eat_times_lock);
		if (check_death(philo))
			return (NULL);
		eating(philo);
		if (check_death(philo))
			return (NULL);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	sleeping(t_philo *philo)
{
	print(philo, "is sleeping");
	ft_sleep(philo->data->time2sleep);
}

void	thinking(t_philo *philo)
{
	print(philo, "is thinking");
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print(philo, "has taken a fork");
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print(philo, "has taken a fork");
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(&philo->last_eat_m);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->last_eat_m);
	print(philo, "\x1B[33mis eating\x1B[0m");
	ft_sleep(philo->data->time2eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (philo->eat_times != -1 && philo->eat_times)
		philo->eat_times--;
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->die_lock);
	if (philo->data->is_die)
	{
		pthread_mutex_unlock(&philo->data->die_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->die_lock);
	return (0);
}
