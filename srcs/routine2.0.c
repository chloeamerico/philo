/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:06:48 by camerico          #+#    #+#             */
/*   Updated: 2025/05/23 15:51:43 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philosophe)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philosophe;
	data = philo->data;
	wait_and_init_routine(philo);
	if (philo->id % 2 == 0)
		decalage_debut_routine(data, philo);
	if (data->nb_of_philo == 1)
		return (routine_for_one(philo), NULL);
	while (!check_simulation_end(data))
	{
		if (check_simulation_end(data))
			break ;
		full_flag(philo);
		if (philo->full_flag == 1)
			break ;
		if (each_philo_action_routine(philo))
			break ;
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
	if (philo_is_eating(philo, philo->data))
		return (1);
	if (philo_is_sleeping(philo, philo->data))
		return (1);
	if (philo_is_thinking(philo, philo->data))
		return (1);
	return (0);
}

void	routine_for_one(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf_action(philo, philo->data, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo);
	printf_action(philo, philo->data, "died");
	pthread_mutex_lock(&philo->data->philo_death_mutex);
	philo->data->philo_death = 1;
	pthread_mutex_unlock(&philo->data->philo_death_mutex);
	pthread_mutex_unlock(philo->left_fork);
}
