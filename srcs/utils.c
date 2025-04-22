/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:54:10 by camerico          #+#    #+#             */
/*   Updated: 2025/04/22 18:30:01 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// // pas sure de l'utiliser
// int	ft_atoi(const char *nptr)
// {
// 	int	i;
// 	int	sign;
// 	int	number;

// 	i = 0;
// 	sign = 1;
// 	number = 0;
// 	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
// 		i++;
// 	if (nptr[i] == '+')
// 		i++;
// 	else if (nptr[i] == '-')
// 	{
// 		sign *= -1;
// 		i++;
// 	}
// 	while (nptr[i] >= '0' && nptr[i] <= '9')
// 	{
// 		number = number * 10 + (nptr[i] - 48);
// 		i++;
// 	}
// 	return (number * sign);
// }


int	check_simulation_end(t_data *data)
{
	int	i = 0;

	pthread_mutex_lock(&data->philo_death_mutex);		// on verifie si il n'y a pas de mort
	if(data->philo_death == 1)
		return (1);
	pthread_mutex_unlock(&data->philo_death_mutex);
	
	if (data->nb_of_meals_required != -1)
	{
		while(i < data->nb_of_philo)
		{
			pthread_mutex_lock(&data->philo->meals_count_mutex);
			if (data->philo->meals_count != data->nb_of_meals_required)
				return (1);
			pthread_mutex_lock(&data->philo->meals_count_mutex);
			i++;
		}
	}
	return(0);
}

//fonction pour verifier si le temps entre 2 repas n'est pas trop long. si oui -> philo mort
void	check_if_dead(t_data *data)
{
	if ((data->philo->last_meal - data->start_time) > data->time_to_die)
	{
		pthread_mutex_lock(&data->philo_death_mutex);
		data->philo_death = 1;
		pthread_mutex_unlock(&data->philo_death_mutex);
	}
}