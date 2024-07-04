/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:22:21 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/06/21 12:22:52 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
}

void	clean_all(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->print);
	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(data->forks + i);
		i++;
	}
	free(data->forks);
}
