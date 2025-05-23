/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:25:06 by camerico          #+#    #+#             */
/*   Updated: 2025/05/22 20:55:38 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	if (data->fork_mutex)
	{
		while (i < data->nb_of_philo)
			pthread_mutex_destroy(&data->fork_mutex[i++]);
		free(data->fork_mutex);
	}
	i = 0;
	if (data->philo)
	{
		while (i < data->nb_of_philo)
		{
			pthread_mutex_destroy(&data->philo[i].meals_count_mutex);
			pthread_mutex_destroy(&data->philo[i].last_meal_mutex);
			i++;
		}
		free(data->philo);
	}
	pthread_mutex_destroy(&data->philo_death_mutex);
	pthread_mutex_destroy(&data->printf_mutex);
	pthread_mutex_destroy(&data->start_simulation_mutex);
	exit(0);
}

void	ft_exit_error(char *message, t_data	*data)
{
	printf("%s\n", message);
	if (data)
		free(data->philo);
	exit(EXIT_FAILURE);
}
