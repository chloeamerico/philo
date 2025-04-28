/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:06:48 by camerico          #+#    #+#             */
/*   Updated: 2025/04/28 18:31:13 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


//etape de prendre les fourchettes
int	take_fork(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->left_fork); // on bloque le mutex de la fourchette de gauche
	if(check_simulation_end(data))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	printf_action(philo, data, "has taken a fork");
	
	pthread_mutex_lock(philo->right_fork); // on bloque le mutex de la fourchette de droite
	if(check_simulation_end(data))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	printf_action(philo, data, "has taken a fork");

	return (0);
}


int	philo_is_eating(t_philo *philo, t_data *data)
{
	if(take_fork(philo, data))
		return (1);
	printf_action(philo, data, "is eating");
	
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_in_ms();		//met a jour le last_meal
	pthread_mutex_unlock(&philo->last_meal_mutex);
	
	if (data->nb_of_meals_required != -1)
	{
		pthread_mutex_lock(&philo->meals_count_mutex);
		philo->meals_count++;
		pthread_mutex_unlock(&philo->meals_count_mutex);
	}
	usleep(data->time_to_eat * 1000);
	
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	
	return (0);
}

void	printf_action(t_philo *philo, t_data *data, char *str)
{
	pthread_mutex_lock(&data->printf_mutex);
	printf("%ld %d %s\n", (get_time_in_ms() - data->start_time), philo->id, str);
	pthread_mutex_unlock(&data->printf_mutex);
}

int	philo_is_thinking(t_philo *philo, t_data *data)
{
	if (check_simulation_end(data))
		return (1);
	printf_action(philo, data, "is thinking");
	return (0);
}

int	philo_is_sleeping(t_philo *philo, t_data *data)
{
	if (check_simulation_end(data))
		return (1);
	printf_action(philo, data, "is sleeping");
	usleep(data->time_to_sleep * 1000);
	return (0);
}

// void *routine(void *arg)
// {
// 	t_philo	*philo = (t_philo *)arg;
// 	t_data *data = philo->data;
	
// 	if (data->nb_of_philo == 1)
// 	{
// 		routine_for_one(data);
// 		return(NULL);
// 	}
// 	while (1) // tant qu'aucun philo n'est pas mort, on continue la simulation
// 	{
// 		pthread_mutex_lock(&data->philo_death_mutex); //on bloque le mutex du nb de morts, on peut le check, puis le debloquer
// 		if (data->philo_death != 0)
// 		{
// 			pthread_mutex_unlock(&data->philo_death_mutex);
// 			break;
// 		}
// 		pthread_mutex_unlock(&data->philo_death_mutex);
// 		philo_is_thinking(philo, data);
// 		philo_is_eating(philo, data);
// 		philo_is_sleeping(philo, data);
// 	}
// 	return (NULL);
// }


void *routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_data *data = philo->data;
	
	if (data->nb_of_philo == 1)
	{
		routine_for_one(data);
		return(NULL);
	}
	if (philo->id % 2 == 0)
		usleep(500);			// on decale un peu le temps de debut pour certains
	while (check_simulation_end(data) == 0) // tant qu'aucun philo n'est pas mort, on continue la simulation
	{										//ou while (1) ??
		philo_is_thinking(philo, data);
		if(check_simulation_end(data))
			break;
		philo_is_eating(philo, data);
		if(check_simulation_end(data))
			break;
		philo_is_sleeping(philo, data);
		usleep(100);
	}
	return (NULL);
}
void	routine_for_one(t_data *data)
{
//	pthread_mutex_lock(data->philo[0].left_fork); // on bloque le mutex de la fourchette de gauche
	printf_action(&data->philo[0], data, "has taken a fork");
	usleep(data->time_to_die);
//	pthread_mutex_unlock(data->philo[0].left_fork);
	printf_action(&data->philo[0], data, "died");
	pthread_mutex_lock(&data->philo_death_mutex);
	data->philo_death = 1;
	pthread_mutex_unlock(&data->philo_death_mutex);
}