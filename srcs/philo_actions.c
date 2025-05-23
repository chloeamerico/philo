/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:04:56 by camerico          #+#    #+#             */
/*   Updated: 2025/05/23 19:49:13 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_sleeping(t_philo *philo, t_data *data)
{
	if (check_simulation_end(data))
		return (1);
	printf_action(philo, data, "is sleeping");
	if (ft_usleep(data->time_to_sleep, philo))
		return (1);
	return (0);
}

int	take_fork(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		printf_action(philo, data, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		printf_action(philo, data, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		printf_action(philo, data, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		printf_action(philo, data, "has taken a fork");
	}
	return (0);
}

int	philo_is_eating(t_philo *philo, t_data *data)
{
	if (take_fork(philo, data))
		return (1);
	printf_action(philo, data, "is eating");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (ft_usleep(data->time_to_eat, philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	if (data->nb_of_meals_required != -1)
	{
		pthread_mutex_lock(&philo->meals_count_mutex);
		philo->meals_count++;
		pthread_mutex_unlock(&philo->meals_count_mutex);
		full_flag(philo);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	philo_is_thinking(t_philo *philo, t_data *data)
{
	long long	since_last_meal;
	long long	time_before_died;
	long long	thinking_delay;

	if (check_simulation_end(data))
		return (1);
	printf_action(philo, data, "is thinking");
	if (data->nb_of_philo % 2 == 1)
	{
		pthread_mutex_lock(&philo->last_meal_mutex);
		since_last_meal = get_time_in_ms() - philo->last_meal;
		pthread_mutex_unlock(&philo->last_meal_mutex);
		time_before_died = data->time_to_die - since_last_meal;
		thinking_delay = (data->time_to_eat + data->time_to_sleep) / 2;
		if (thinking_delay > time_before_died)
			return (1);
		if (ft_usleep(thinking_delay, philo))
			return (1);
	}
	return (0);
}
