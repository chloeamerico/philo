/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:06:48 by camerico          #+#    #+#             */
/*   Updated: 2025/05/22 17:19:54 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *philosophe)
{
	t_philo	*philo = (t_philo *)philosophe;
	t_data *data = philo->data;
	
	wait_and_init_routine(philo);
	if (philo->id % 2 == 0)		// si les philos sont pairs, on decale un peu le temps de debut pour certains
	{
		if (ft_usleep((data->time_to_die - (data->time_to_eat + data->time_to_sleep)) / 2, philo))
			return(NULL);			// est ce que je peux return (0) sur un void ??			
	}
	if (data->nb_of_philo == 1)
		return(routine_for_one(philo), NULL);
	while (!check_simulation_end(data)) // tant que c'est vrai, on continue la simulation
	{
		if(check_simulation_end(data))
			break;
		// full_flag(philo);
		if (philo->full_flag)		// verifie si CE phlo est deja plein
		{
			printf("%d is full et quiite la routine\n", philo->id);	
			break;
		}
		if (each_philo_action_routine(philo))
			break;
	}
	return (NULL);
}

void	wait_and_init_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->start_simulation_mutex);
	pthread_mutex_unlock(&philo->data->start_simulation_mutex);
	
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
}

int	each_philo_action_routine(t_philo *philo)
{
	if(philo_is_eating(philo, philo->data))
		return(1);
	if (philo_is_sleeping(philo, philo->data))
		return (1);
	if (philo_is_thinking(philo, philo->data))
		return (1);
	return (0);
}

void	routine_for_one(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork); // on bloque le mutex de la fourchette de gauche
	printf_action(philo, philo->data, "has taken a fork");
	
	// usleep(philo->data->time_to_die * 1000);
	ft_usleep(philo->data->time_to_die, philo);
	
	printf_action(philo, philo->data, "died");

	pthread_mutex_lock(&philo->data->philo_death_mutex);
	philo->data->philo_death = 1;
	pthread_mutex_unlock(&philo->data->philo_death_mutex);

	pthread_mutex_unlock(philo->left_fork);
}

// //etape de prendre les fourchettes
// //ancienne fonction
// int	take_fork(t_philo *philo, t_data *data)
// {
// 	if(check_simulation_end(data))
// 		return (1);
// 	pthread_mutex_lock(philo->left_fork); // on bloque le mutex de la fourchette de gauche
// 	printf_action(philo, data, "has taken a fork");
// 	if(check_simulation_end(data))
// 	{
// 		pthread_mutex_unlock(philo->left_fork);
// 		return (1);
// 	}
// 	pthread_mutex_lock(philo->right_fork); // on bloque le mutex de la fourchette de droite
// 	if(check_simulation_end(data))
// 	{
// 		pthread_mutex_unlock(philo->left_fork);
// 		pthread_mutex_unlock(philo->right_fork);
// 		return (1);
// 	}
// 	printf_action(philo, data, "has taken a fork");
// 	return (0);
// }
//nouvelle fonction
int take_fork(t_philo *philo, t_data *data)
{
    if(check_simulation_end(data))
        return (1);
        
    if (philo->id % 2 == 0) // pour les philo pairs, commencent par la right_fork
    {
        pthread_mutex_lock(philo->right_fork);
        printf_action(philo, data, "has taken a fork");
        if(check_simulation_end(data))
        {
            pthread_mutex_unlock(philo->right_fork);
            return (1);
        }
        pthread_mutex_lock(philo->left_fork);
        if(check_simulation_end(data))
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
            return (1);
        }
    }
    else		// pour les philo pairs, commencent par la left_fork
    {
        pthread_mutex_lock(philo->left_fork);
        printf_action(philo, data, "has taken a fork");
        if(check_simulation_end(data))
        {
            pthread_mutex_unlock(philo->left_fork);
            return (1);
        }
        
        pthread_mutex_lock(philo->right_fork);
        if(check_simulation_end(data))
        {
            pthread_mutex_unlock(philo->left_fork);
            pthread_mutex_unlock(philo->right_fork);
    		return (1);
        }
    }
    printf_action(philo, data, "has taken a fork");
    return (0);
}

// // a retravailler
// // For even-numbered philosophers, take right fork first
// if (philo->id % 2 == 0) {
//     pthread_mutex_lock(philo->right_fork);
//     printf_action(philo, data, "has taken a fork");
//     pthread_mutex_lock(philo->left_fork);
//     printf_action(philo, data, "has taken a fork");
// } else { // For odd-numbered, take left fork first
//     pthread_mutex_lock(philo->left_fork);
//     printf_action(philo, data, "has taken a fork");
//     pthread_mutex_lock(philo->right_fork);
//     printf_action(philo, data, "has taken a fork");
// }

int	philo_is_eating(t_philo *philo, t_data *data)
{
	if(check_simulation_end(data))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return(1);
	}
	if(take_fork(philo, data))
		return (1);
	if(check_simulation_end(data))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return(1);
	}
	printf_action(philo, data, "is eating");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_in_ms();		//met a jour le last_meal
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (data->nb_of_meals_required != -1)
	{
		pthread_mutex_lock(&philo->meals_count_mutex);
		philo->meals_count++;
		if (philo->meals_count == data->nb_of_meals_required)
		{
			philo->full_flag = 1;
			// printf("%d finished eating\n", philo->id);
		}
		pthread_mutex_unlock(&philo->meals_count_mutex);
		
	}
	if(ft_usleep(data->time_to_eat, philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return(1);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	printf_action(t_philo *philo, t_data *data, char *str)
{
	if (check_simulation_end(data))
		return;
	pthread_mutex_lock(&data->printf_mutex);
	printf("%lld %d %s\n", (get_time_in_ms() - data->start_time), philo->id, str);
	pthread_mutex_unlock(&data->printf_mutex);
}

int	philo_is_thinking(t_philo *philo, t_data *data)
{
	long long	since_last_meal;
	long long	time_before_died;
	long long	thinking_delay;
	
	if (check_simulation_end(data))
		return (1);

	printf_action(philo, data, "is thinking");
	
	if (data->nb_of_philo % 2 == 1) 	// si il y a un nb impaire de philo...
	{
		pthread_mutex_lock(&philo->last_meal_mutex);
		since_last_meal = get_time_in_ms() - philo->last_meal;
		pthread_mutex_unlock(&philo->last_meal_mutex);

		time_before_died = data->time_to_die - since_last_meal;
		thinking_delay = (data->time_to_eat + data->time_to_sleep) / 2;
		
		if (thinking_delay > time_before_died)		// on verifie si il n'a pas le temps de penser, on passe direct a l'action suivante
			return (1);
		
		if(ft_usleep(thinking_delay, philo))
			return(1);
	}
	return (0);
}

int	philo_is_sleeping(t_philo *philo, t_data *data)
{
	if (check_simulation_end(data))
		return (1);
	printf_action(philo, data, "is sleeping");
	if(ft_usleep(data->time_to_sleep, philo))
		return(1);
	return (0);
}


int	ft_usleep(long time_to_sleep, t_philo *philo)
{
	long	start_sleep;					// peut-etre passer en long long
	long	interval;

	start_sleep = get_time_in_ms();
	interval = get_time_in_ms() - start_sleep;

	while(interval < time_to_sleep)
	{
		pthread_mutex_lock(&philo->data->philo_death_mutex);
		if(philo->data->philo_death == 1)
		{
			pthread_mutex_unlock(&philo->data->philo_death_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->philo_death_mutex);
		usleep(100);
		interval = get_time_in_ms() - start_sleep;
	}
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

