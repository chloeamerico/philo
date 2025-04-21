/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:06:48 by camerico          #+#    #+#             */
/*   Updated: 2025/04/21 18:13:32 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void routine(t_data *data)
{
	int	i = 0;
	
	while (data->philo_death == 0) // tant qu'aucun philo n'est pas mort, on comtinue la simulation
	{
		//etape de penser
		pthread_mutex_lock(&data->printf_mutex);
		printf("%lg %d is thinking\n", get_time_in_ms(), &data->philo[i]->id);
		pthread_mutex_unlock(&data->printf_mutex);

		//etape de prendre les fourchettes
		pthread_mutex_lock(data->philo->left_fork); // on bloque le mutex de la fourchette de gauche
			pthread_mutex_lock(&data->printf_mutex);// on bloque le mutex d'ecriture
			printf("%lg %d X has taken a fork\n", get_time_in_ms(), &data->philo[i]->id);
			pthread_mutex_unlock(&data->printf_mutex);
			
				pthread_mutex_lock(data->philo->right_fork); // on bloque le mutex de la fourchette de droite
				&data.philo[i]->last_meal = get_time_in_ms();
					pthread_mutex_lock(&data->printf_mutex);// on bloque le mutex d'ecriture
					printf("%lg %d X has taken a fork\n", get_time_in_ms(), &data->philo[i]->id);
					pthread_mutex_unlock(&data->printf_mutex);
					if (data->nb_of_meals_required != -1)
						&data.philo[i]->meals_count++;
		
						pthread_mutex_lock(&data->printf_mutex);// on bloque le mutex d'ecriture
						printf("%lg %d X is eating\n", get_time_in_ms(), &data->philo[i]->id);
						pthread_mutex_unlock(&data->printf_mutex);
						
		pthread_mutex_unlock(data->philo->left_fork);
		pthread_mutex_unlock(data->philo->right_fork);

		//etape pour dormir
		pthread_mutex_lock(&data->printf_mutex);
		printf("%lg %d is sleeping\n", get_time_in_ms(), &data->philo[i]->id);
		pthread_mutex_unlock(&data->printf_mutex);
	}
}
