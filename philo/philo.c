/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:27:54 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/06/29 10:58:57 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ll(void)
{
	printf("\n\n------------------------\n");
	system("leaks -q philo");
	printf("------------------------\n");
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	// atexit(ll);
	if (chech_command_line(ac, av) != 0)
		return (1);
	if (init_struct(&data, ac, av))
		return (1);
	philos = malloc(data.philo_nb * sizeof(t_philo));
	if (!philos)
		return (1);
	if (init_philos(&data, philos))
		return (1);
	if (create_threads(&data, philos))
		return (1);
	while (!ft_check(philos))
		;
	join_threads(&data, philos);
	clean_all(&data);
	free(philos);
	return (0);
}

int	ft_check(t_philo *philo)
{
	int	i;
	int	t;

	i = -1;
	t = 0;
	while (++i < philo->data->philo_nb)
	{
		if (ft_get_time() - philo[i].last_eat >= philo->data->time2die)
		{
			death(philo + i);
			return (1);
		}
		if (!philo[i].eat_times)
			t++;
		if (t == philo->data->philo_nb)
		{
			pthread_mutex_lock(&philo[i].data->eat_times_lock);
			philo->data->eat_times = 0;
			pthread_mutex_unlock(&philo[i].data->eat_times_lock);
			return (1);
		}
	}
	return (0);
}
