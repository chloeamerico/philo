/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:54:10 by camerico          #+#    #+#             */
/*   Updated: 2025/05/23 17:56:36 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//on verifie si la simulation doit stop : soit 1 mort , soit ils ont ts mange
//return(0) si on continue la simulation, return (1) si on doit l'arreter
int	check_simulation_end(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->philo_death_mutex);
	if (data->philo_death == 1)
		return (pthread_mutex_unlock(&data->philo_death_mutex), 1);
	pthread_mutex_unlock(&data->philo_death_mutex);
	if (data->nb_of_meals_required != -1)
	{
		while (i < data->nb_of_philo)
		{
			pthread_mutex_lock(&data->philo[i].meals_count_mutex);
			if (data->philo[i].full_flag == 0)
			{
				pthread_mutex_unlock(&data->philo[i].meals_count_mutex);
				return (0);
			}
			pthread_mutex_unlock(&data->philo[i].meals_count_mutex);
			i++;
		}
		if (i == data->nb_of_philo)
			return (1);
	}
	return (0);
}

//fonction pour verifier si le temps entre 2 repas n'est pas trop long.
//si oui -> philo mort
void	check_if_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_lock(&data->philo[i].last_meal_mutex);
		if ((get_time_in_ms() - data->philo[i].last_meal) > data->time_to_die)
		{
			pthread_mutex_lock(&data->philo_death_mutex);
			data->philo_death = 1;
			pthread_mutex_unlock(&data->philo_death_mutex);
			pthread_mutex_lock(&data->printf_mutex);
			printf("%lld %d died\n", (get_time_in_ms() - data->start_time),
				data->philo[i].id);
			pthread_mutex_unlock(&data->printf_mutex);
			pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
			return ;
		}
		pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
		i++;
	}
}

//monitor qui va appeler les fonctions check_if_dead et 
//check_simulation_end en boucle tant que la simulation tourne
void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *) arg;
	while (1)
	{
		check_if_dead(data);
		if (check_simulation_end(data) == 1)
			break ;
		usleep(100);
	}
	return (NULL);
}

void	full_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_count_mutex);
	if (philo->meals_count == philo->data->nb_of_meals_required)
	{
		philo->full_flag = 1;
	}
	pthread_mutex_unlock(&philo->meals_count_mutex);
}
