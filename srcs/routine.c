/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:06:48 by camerico          #+#    #+#             */
/*   Updated: 2025/04/21 19:08:02 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_data *data = philo->data;
	
	while (data->philo_death == 0) // tant qu'aucun philo n'est pas mort, on comtinue la simulation
	{
		//etape de penser
		pthread_mutex_lock(&data->printf_mutex);
		printf("%ld %d is thinking\n", (get_time_in_ms() - data->start_time), philo->id);
		pthread_mutex_unlock(&data->printf_mutex);

		//etape de prendre les fourchettes
		pthread_mutex_lock(philo->left_fork); // on bloque le mutex de la fourchette de gauche
			pthread_mutex_lock(&data->printf_mutex);// on bloque le mutex d'ecriture
			printf("%ld %d has taken a fork\n", (get_time_in_ms() - data->start_time), philo->id);
			pthread_mutex_unlock(&data->printf_mutex);
			
				pthread_mutex_lock(philo->right_fork); // on bloque le mutex de la fourchette de droite
				philo->last_meal = get_time_in_ms();
					pthread_mutex_lock(&data->printf_mutex);// on bloque le mutex d'ecriture
					printf("%ld %d has taken a fork\n", (get_time_in_ms() - data->start_time), philo->id);
					pthread_mutex_unlock(&data->printf_mutex);
					if (data->nb_of_meals_required != -1)
						philo->meals_count++;
		
						pthread_mutex_lock(&data->printf_mutex);// on bloque le mutex d'ecriture
						printf("%ld %d is eating\n", (get_time_in_ms() - data->start_time), philo->id);
						pthread_mutex_unlock(&data->printf_mutex);
						usleep(data->time_to_eat * 1000);
						
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		//etape pour dormir
		pthread_mutex_lock(&data->printf_mutex);
		printf("%ld %d is sleeping\n", (get_time_in_ms() - data->start_time), philo->id);
		pthread_mutex_unlock(&data->printf_mutex);
		usleep(data->time_to_sleep * 1000);
	}
}
