/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:54:10 by camerico          #+#    #+#             */
/*   Updated: 2025/05/16 16:45:57 by camerico         ###   ########.fr       */
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

//on verifie si la simulation doit s'arreter : soit 1 mort , soit ils ont tous mange
//return(0) si on continue la simulation, return (1) si on doit l'arreter
int	check_simulation_end(t_data *data)
{
	int	i = 0;

	pthread_mutex_lock(&data->philo_death_mutex);		// on verifie si il n'y a pas de mort
	if(data->philo_death == 1)
	{
		pthread_mutex_unlock(&data->philo_death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->philo_death_mutex);
	
	if (data->nb_of_meals_required != -1) // check le full flag
	{
		while(i < data->nb_of_philo)
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
			return(1);
	}
	return(0);
}


//fonction pour verifier si le temps entre 2 repas n'est pas trop long. si oui -> philo mort
void	check_if_dead(t_data *data)
{
	int	i = 0;
	while(i < data->nb_of_philo)
	{
		pthread_mutex_lock(&data->philo[i].last_meal_mutex);
		if ((get_time_in_ms() - data->philo[i].last_meal) > data->time_to_die)
		{
			pthread_mutex_lock(&data->philo_death_mutex);
			data->philo_death = 1;
			pthread_mutex_unlock(&data->philo_death_mutex);
			pthread_mutex_lock(&data->printf_mutex);
			printf_action(&data->philo[i], data, "died");		// on affiche qu'un philo est mort
			pthread_mutex_unlock(&data->printf_mutex);
			return;
		}
		pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
		i++;
	}
}

//monitor qui va appeler les fonctions check_if_dead et check_simulation_end en boucle tant que la simulation tourne
void	*monitor(void *arg)
{
	t_data	*data = (t_data *) arg;

	while(1)
	{
		check_if_dead(data);
		if(check_simulation_end(data) == 1)
			break;
		usleep(100);
	}
	return (NULL);
}

void	full_flag(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data->nb_of_meals_required != -1)
	{
		while(i < philo->data->nb_of_philo)
		{
			pthread_mutex_lock(&philo[i].meals_count_mutex);
			if (philo[i].last_meal == philo->data->nb_of_meals_required)
				philo[i].full_flag = 1;
			pthread_mutex_unlock(&philo[i].meals_count_mutex);
			i++;
		}
	}
}