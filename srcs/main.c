/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:43:16 by camerico          #+#    #+#             */
/*   Updated: 2025/04/14 16:14:17 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of arguments");
		return(1);
	}
	
	init_struct(argv, &data, argc);
	creation_mutex(&data);
	creation_threads(&data);

}

void	init_struct(char **argv, t_data *data, int argc)
{
	data->nb_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_of_meals_required = ft_atoi(argv[5]);
	else
		data->nb_of_meals_required = -1;
}

void	creation_mutex(t_data *data)
{
	int	i = 0;
	
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->fork_mutex)
	{
		printf("Error : malloc mutex\n");
		return(0);
	}
	while(i < data->nb_of_philo)
	{
		if(pthread_mutex_init(&data->fork_mutex[i], NULL) != 0)
		{
			printf("Error : init mutex\n");
			return (0);
		}
		i++;
	}
}

void	creation_threads(t_data *data)
{
	int	i = 0;
	// pthread_t	*philo_thread;
	
	data->thread = malloc(sizeof(pthread_t) * data->nb_of_philo);
	if (!data->thread)
	{
		printf("Error : malloc thread\n");
		return(0);
	}
	while(i < data->nb_of_philo)
	{
		if(pthread_create(&data->thread[i], NULL, routine, data) != 0)
		{
			printf("Error : create threads\n");
			return (0);
		}
		i++;
	}
}

void	routine(t_data *data)
{
	// ecrire la routine de chaque philo
	// dormir, penser, manger...
}