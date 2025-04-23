/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:25:06 by camerico          #+#    #+#             */
/*   Updated: 2025/04/23 18:37:08 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data)
{
	int i;

	//on detruit les mutex de fourchettes
	i = 0;
	while(i < data->nb_of_philo)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);		
		i++;
	}
	//on detruit les mutex de meals_count
	i = 0;
	while(i < data->nb_of_philo)
	{
		pthread_mutex_destroy(&data->philo[i].meals_count_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->philo_death_mutex);
	pthread_mutex_destroy(&data->printf_mutex);	
	
	free(data->thread);
	free(data->philo);
}