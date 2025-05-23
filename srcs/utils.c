/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:06:04 by camerico          #+#    #+#             */
/*   Updated: 2025/05/23 18:15:27 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//fonction qui va renvoyer le temps (en millisec)
long long	get_time_in_ms(void)
{
	struct timeval	tv;
	long			actual_time;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	actual_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (actual_time);
}

int	ft_usleep(long time_to_sleep, t_philo *philo)
{
	long	start_sleep;
	long	interval;

	start_sleep = get_time_in_ms();
	interval = get_time_in_ms() - start_sleep;
	while (interval < time_to_sleep)
	{
		pthread_mutex_lock(&philo->data->philo_death_mutex);
		if (philo->data->philo_death == 1)
		{
			pthread_mutex_unlock(&philo->data->philo_death_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->philo_death_mutex);
		usleep(100);
		interval = get_time_in_ms() - start_sleep;
	}
	return (0);
}

void	printf_action(t_philo *philo, t_data *data, char *str)
{
	if (check_simulation_end(data))
		return ;
	pthread_mutex_lock(&data->printf_mutex);
	printf("%lld %d %s\n", (get_time_in_ms() - data->start_time),
		philo->id, str);
	pthread_mutex_unlock(&data->printf_mutex);
}

void	decalage_debut_routine(t_data *data, t_philo *philo)
{
	long long	time_eat_and_sleep;

	time_eat_and_sleep = data->time_to_eat + data->time_to_sleep;
	ft_usleep((data->time_to_die - (time_eat_and_sleep)) / 2, philo);
}
