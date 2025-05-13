/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:25:06 by camerico          #+#    #+#             */
/*   Updated: 2025/05/13 15:54:48 by camerico         ###   ########.fr       */
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
		pthread_mutex_destroy(&data->philo[i].meals_count_mutex);
		pthread_mutex_destroy(&data->philo[i].last_meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->philo_death_mutex);
	pthread_mutex_destroy(&data->printf_mutex);
	
	// if(data->thread)
	// 	free(data->thread);		si pas de malloc de threads -> pas de free
	if(data->philo)
		free(data->philo);
	if(data->fork_mutex)
		free(data->fork_mutex);
}


//du coup peut etre pas necessaire vu que j'appelle maintenant free_all a la place
//si un mutex ne s'initialise pas, on detruit tous ceux deja initialises
void	destroy_mutex(int nb_mutex, t_data *data)
{
	int	i = 0;
	
	while(i < nb_mutex)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);
		i++;
	}
}

void	ft_exit_error(char *message, t_data	*data)
{
	printf("%s\n", message);
	if(data)
	{
		// free(data->thread);
		free(data->philo);
	}
	exit(EXIT_FAILURE);
}