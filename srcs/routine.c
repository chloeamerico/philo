/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:06:48 by camerico          #+#    #+#             */
/*   Updated: 2025/04/24 19:21:04 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// void routine(void *arg)
// {
// 	t_philo	*philo = (t_philo *)arg;
// 	t_data *data = philo->data;
	
// 	while (1) // tant qu'aucun philo n'est pas mort, on comtinue la simulation
// 	{
// 		pthread_mutex_lock(&data->philo_death_mutex); //on bloque le mutex du nb de motre, on peut le check, puis le debloquer
// 		if (data->philo_death != 0)
// 		{
// 			pthread_mutex_unlock(&data->philo_death_mutex);
// 			break;
// 		}
// 		pthread_mutex_unlock(&data->philo_death_mutex);
		
// 		//etape de penser
// 		pthread_mutex_lock(&data->printf_mutex);
// 		printf("%ld %d is thinking\n", (get_time_in_ms() - data->start_time), philo->id);
// 		pthread_mutex_unlock(&data->printf_mutex);

// 		//etape de prendre les fourchettes
// 		pthread_mutex_lock(philo->left_fork); // on bloque le mutex de la fourchette de gauche
// 			pthread_mutex_lock(&data->printf_mutex);// on bloque le mutex d'ecriture
// 			printf("%ld %d has taken a fork\n", (get_time_in_ms() - data->start_time), philo->id);
// 			pthread_mutex_unlock(&data->printf_mutex);
			
// 				pthread_mutex_lock(philo->right_fork); // on bloque le mutex de la fourchette de droite
// 				philo->last_meal = get_time_in_ms();
// 					pthread_mutex_lock(&data->printf_mutex);// on bloque le mutex d'ecriture
// 					printf("%ld %d has taken a fork\n", (get_time_in_ms() - data->start_time), philo->id);
// 					pthread_mutex_unlock(&data->printf_mutex);
// 					if (data->nb_of_meals_required != -1)
// 						philo->meals_count++;
		
// 						pthread_mutex_lock(&data->printf_mutex);// on bloque le mutex d'ecriture
// 						printf("%ld %d is eating\n", (get_time_in_ms() - data->start_time), philo->id);
// 						pthread_mutex_unlock(&data->printf_mutex);
// 						usleep(data->time_to_eat * 1000);
						
// 		pthread_mutex_unlock(philo->left_fork);
// 		pthread_mutex_unlock(philo->right_fork);

// 		//etape pour dormir
// 		pthread_mutex_lock(&data->printf_mutex);
// 		printf("%ld %d is sleeping\n", (get_time_in_ms() - data->start_time), philo->id);
// 		pthread_mutex_unlock(&data->printf_mutex);
// 		usleep(data->time_to_sleep * 1000);
// 	}
// }

// void routine(void *arg)
// {
// 	t_philo	*philo = (t_philo *)arg;
// 	t_data *data = philo->data;
	
// 	while (1) // tant qu'aucun philo n'est pas mort, on comtinue la simulation
// 	{
// 		pthread_mutex_lock(&data->philo_death_mutex); //on bloque le mutex du nb de motre, on peut le check, puis le debloquer
// 		if (data->philo_death != 0)
// 		{
// 			pthread_mutex_unlock(&data->philo_death_mutex);
// 			break;
// 		}
// 		pthread_mutex_unlock(&data->philo_death_mutex);

// 		//etape de penser
// 		pthread_mutex_lock(&data->printf_mutex);
// 		printf("%ld %d is thinking\n", (get_time_in_ms() - data->start_time), philo->id);
// 		pthread_mutex_unlock(&data->printf_mutex);

// 		//etape de prendre les fourchettes
// 		pthread_mutex_lock(philo->left_fork); // on bloque le mutex de la fourchette de gauche
// 			pthread_mutex_lock(&data->printf_mutex);// on bloque le mutex d'ecriture
// 			printf("%ld %d has taken a fork\n", (get_time_in_ms() - data->start_time), philo->id);
// 			pthread_mutex_unlock(&data->printf_mutex);
			
// 				pthread_mutex_lock(philo->right_fork); // on bloque le mutex de la fourchette de droite
// 				philo->last_meal = get_time_in_ms();
// 					pthread_mutex_lock(&data->printf_mutex);// on bloque le mutex d'ecriture
// 					printf("%ld %d has taken a fork\n", (get_time_in_ms() - data->start_time), philo->id);
// 					pthread_mutex_unlock(&data->printf_mutex);
// 					if (data->nb_of_meals_required != -1)
// 						philo->meals_count++;		// peut-etre le proteger avec un mutex
		
// 						pthread_mutex_lock(&data->printf_mutex);// on bloque le mutex d'ecriture
// 						printf("%ld %d is eating\n", (get_time_in_ms() - data->start_time), philo->id);
// 						pthread_mutex_unlock(&data->printf_mutex);
// 						usleep(data->time_to_eat * 1000);

// 		pthread_mutex_unlock(philo->left_fork);
// 		pthread_mutex_unlock(philo->right_fork);

// 		//etape pour dormir
// 		pthread_mutex_lock(&data->printf_mutex);
// 		printf("%ld %d is sleeping\n", (get_time_in_ms() - data->start_time), philo->id);
// 		pthread_mutex_unlock(&data->printf_mutex);
// 		usleep(data->time_to_sleep * 1000);
// 	}
// 	return (NULL);
// }

//etape de prendre les fourchettes
int	take_fork(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->left_fork); // on bloque le mutex de la fourchette de gauche
	printf_action(philo, data, "has taken a fork");
	
	pthread_mutex_lock(philo->right_fork); // on bloque le mutex de la fourchette de droite
	printf_action(philo, data, "has taken a fork");

	return (0);
}


int	philo_is_eating(t_philo *philo, t_data *data)
{
	take_fork(philo, data);
	printf_action(philo, data, "is eating");
	philo->last_meal = get_time_in_ms();
	if (data->nb_of_meals_required != -1)
	{
		pthread_mutex_lock(&philo->meals_count_mutex);
		philo->meals_count++;		// peut-etre le proteger avec un mutex
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
	printf_action(philo, data, "is thinking");
	return (0);
}

int	philo_is_sleeping(t_philo *philo, t_data *data)
{
	printf_action(philo, data, "is sleeping");
	usleep(data->time_to_sleep * 1000);
	return (0);
}

void *routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_data *data = philo->data;
	
	if (data->nb_of_philo == 1)
	{
		routine_for_one(data);
		return(NULL);
	}
	while (1) // tant qu'aucun philo n'est pas mort, on continue la simulation
	{
		pthread_mutex_lock(&data->philo_death_mutex); //on bloque le mutex du nb de morts, on peut le check, puis le debloquer
		if (data->philo_death != 0)
		{
			pthread_mutex_unlock(&data->philo_death_mutex);
			break;
		}
		pthread_mutex_unlock(&data->philo_death_mutex);
		philo_is_thinking(philo, data);
		philo_is_eating(philo, data);
		philo_is_sleeping(philo, data);
	}
	return (NULL);
}

void	routine_for_one(t_data *data)
{
	pthread_mutex_lock(data->philo[0].left_fork); // on bloque le mutex de la fourchette de gauche
	printf_action(&data->philo[0], data, "has taken a fork");
	usleep(data->time_to_die);
	pthread_mutex_unlock(data->philo[0].left_fork);
	printf_action(&data->philo[0], data, "died");
}