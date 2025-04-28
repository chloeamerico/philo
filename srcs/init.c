/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:28:40 by camerico          #+#    #+#             */
/*   Updated: 2025/04/28 17:40:15 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(char **argv, t_data *data, int argc)
{
	data->nb_of_philo = (int)ft_atol(argv[1]);
	data->time_to_die = (int)ft_atol(argv[2]);
	data->time_to_eat = (int)ft_atol(argv[3]);
	data->time_to_sleep = (int)ft_atol(argv[4]);
	if (argc == 6)
		data->nb_of_meals_required = ft_atol(argv[5]);
	else
		data->nb_of_meals_required = -1;
	data->start_time = get_time_in_ms();
	data->philo_death = 0;
}


void	creation_mutex(t_data *data)
{
	int	i = 0;

	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->fork_mutex)
	{
		printf("Error : malloc mutex\n");
		free_all(data);
		exit(1);		//est ce que c'est bien de faire exit ??
	}
	while(i < data->nb_of_philo)
	{
		if(pthread_mutex_init(&data->fork_mutex[i], NULL) != 0)
		{
			printf("Error : init mutex\n");
			free_all(data);
			exit(1);
		}
		i++;
	}
	ft_mutex_init(&data->philo_death_mutex, data);
	ft_mutex_init(&data->printf_mutex, data);
}


void	init_philo_tab(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philo)
	{
		printf("Error : malloc philo tab\n");
		exit(1);
	}
	while(i < data->nb_of_philo)
	{
		data->philo[i].id = i + 1;		// pour que le 1er philo soit le 1 et pas le 0
		data->philo[i].left_fork = &data->fork_mutex[i];
		data->philo[i].right_fork = &data->fork_mutex[(i + 1) % data->nb_of_philo];
		data->philo[i].meals_count = 0;
		data->philo[i].data = data;
		data->philo[i].last_meal = data->start_time;
		ft_mutex_init(&data->philo[i].meals_count_mutex, data);
		ft_mutex_init(&data->philo[i].last_meal_mutex, data);
		i++;
	}
}

void	ft_mutex_init(pthread_mutex_t *mutex, t_data *data)
{
	if (pthread_mutex_init(mutex, NULL))
	{
		printf("Error : init mutex\n");
		free_all(data);
		exit(1);
	}
}


void	creation_threads(t_data *data)
{
	int	i = 0;

	
	data->thread = malloc(sizeof(pthread_t) * data->nb_of_philo); // +1 pour le thread monitor
	if (!data->thread)
	{
		printf("Error : malloc thread\n");
		exit(1);
	}
	while(i < data->nb_of_philo)
	{
		if(pthread_create(&data->thread[i], NULL, routine, &data->philo[i]) != 0) // le &data->philo[i] permet a chaque philo d'acceder a sa propre structure
		{
			printf("Error : create threads\n");
			exit(1);
		}
		i++;
	}
	pthread_create(&data->monitor_thread, NULL, monitor, &data); //fonction monitor a creer;
}