/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:28:26 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/06/23 17:50:56 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				philo_nb;
	int				time2eat;
	int				time2sleep;
	int				time2die;
	int				eat_times;
	long			start_time;
	int				is_die;
	pthread_mutex_t	die_lock;
	pthread_mutex_t	eat_times_lock;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			last_eat;
	pthread_mutex_t	last_eat_m;
	int				eat_times;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_t		philo;
	t_data			*data;
}	t_philo;

int		chech_command_line(int ac, char **av);
int		is_number(char *str);
int		ft_atoi(const char *str);
void	*routine(void *arg);
int		init_struct(t_data *data, int ac, char **av);

int		init_philos(t_data *data, t_philo *philos);
int		create_threads(t_data *data, t_philo *philos);

void	print(t_philo *philo, char *s);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	eating(t_philo *philo);
void	join_threads(t_data *data, t_philo *philos);

void	ft_sleep(long ms);
long	ft_get_time(void);
int		ft_check(t_philo *philos);
int		check_death(t_philo *philo);
void	death(t_philo *philo);
void	clean_all(t_data *data);

#endif
