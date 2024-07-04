/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:34:32 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/06/23 17:23:17 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chech_command_line(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (!is_number(av[1]) || ft_atoi(av[1]) > 200)
			printf("INVALID INPUTS : number of philos is more than 200\n");
		else if (!is_number(av[1]) || ft_atoi(av[1]) < 0)
			printf("INVALID INPUTS : number of philos is less than 0\n");
		else if (!is_number(av[2]) || ft_atoi(av[2]) < 60)
			printf("INVALID INPUTS : time to die is less than 60 ms\n");
		else if (!is_number(av[3]) || ft_atoi(av[3]) < 60)
			printf("INVALID INPUTS : time to eat is less than 60 ms\n");
		else if (!is_number(av[4]) || ft_atoi(av[4]) < 60)
			printf("INVALID INPUTS : time to sleep is less than 60 ms\n");
		else if (ac == 6 && (!is_number(av[5]) || ft_atoi(av[5]) < 0))
			printf("INVALID INPUTS : eat times should be more than 1 times\n");
		else
			return (0);
		return (1);
	}
	else
	{
		printf("INVALID INPUTS\nprototype : ./philo [philos_number] [time2die] \
[time2eat] [time2sleep] [eat_times]\n");
		return (1);
	}
}

int	init_struct(t_data *data, int ac, char **av)
{
	if (pthread_mutex_init(&data->print, NULL))
		return (1);
	if (pthread_mutex_init(&data->die_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->eat_times_lock, NULL))
		return (1);
	data->philo_nb = ft_atoi(av[1]);
	data->time2die = ft_atoi(av[2]);
	data->time2eat = ft_atoi(av[3]);
	data->time2sleep = ft_atoi(av[4]);
	data->is_die = 0;
	if (ac == 6)
		data->eat_times = ft_atoi(av[5]);
	else
		data->eat_times = -1;
	data->forks = malloc(data->philo_nb * sizeof(pthread_mutex_t));
	return (0);
}

int	init_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		if (pthread_mutex_init(&philos[i].last_eat_m, NULL))
			return (1);
		philos[i].data = data;
		philos[i].eat_times = data->eat_times;
		philos[i].id = i + 1;
		philos[i].r_fork = &data->forks[i];
		if (i + 1 != data->philo_nb)
			philos[i].l_fork = &data->forks[i + 1];
		else
			philos[i].l_fork = &data->forks[0];
		i++;
	}
	return (0);
}

int	create_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time();
	while (i < data->philo_nb)
	{
		philos[i].last_eat = data->start_time;
		if (pthread_create(&((philos + i)->philo), NULL, routine,
				(void *)&philos[i]))
			return (1);
		i++;
	}
	return (0);
}
