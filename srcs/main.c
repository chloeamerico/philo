/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:43:16 by camerico          #+#    #+#             */
/*   Updated: 2025/04/23 18:07:54 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int	i = 0;
	
	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of arguments");
		return(1);
	}
	if(check_arg(argc, argv))
	{
		printf("Error arg");
		return (1);
	}
	init_struct(argv, &data, argc);
	creation_mutex(&data);
	init_philo_tab(&data);
	creation_threads(&data);
	while(i < data.nb_of_philo)
	{
		pthread_join(data.thread[i], NULL); // pour attendre 
		i++;
	}
	pthread_join(data.monitor_thread, NULL);
	return(0);
}


void	init_struct(char **argv, t_data *data, int argc)
{
	data->nb_of_philo = (int)ft_atol(argv[1]);
	data->time_to_die = (int)ft_atol(argv[2]);
	data->time_to_eat = (int)ft_atol(argv[3]);
	data->time_to_sleep = (int)ft_atol(argv[4]);
	if (argc == 6)
		data->nb_of_meals_required = ft_atoi(argv[5]);
	else
		data->nb_of_meals_required = -1;
	data->start_time = get_time_in_ms();
}

void	creation_mutex(t_data *data)
{
	int	i = 0;

	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->fork_mutex)
	{
		printf("Error : malloc mutex\n");
		exit(1);		//est ce que c'est bien de faire exit ??
	}
	while(i < data->nb_of_philo)
	{
		if(pthread_mutex_init(&data->fork_mutex[i], NULL) != 0)
		{
			printf("Error : init mutex\n");
			destroy_mutex(i, data);
			exit(1);
		}
		i++;
	}
}

//si un mutex ne s'initialise pas, on detruit tous ceux deja initialises
void	destroy_mutex(int nb_mutex, t_data *data)
{
	int	i = 0;
	
	while(i < nb_mutex)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);
		i++;
	}
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
		i++;
	}
}

void	creation_threads(t_data *data)
{
	int	i = 0;

	
	data->thread = malloc(sizeof(pthread_t) * data->nb_of_philo + 1); // +1 pour le thread monitor
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

// void	routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	// ecrire la routine de chaque philo
// 	// dormir, penser, manger...

// 	// mettre a jour le last meal avant qu'il commence son premier repas
// }

//fonction qui va renvoyer le temps (en millisec)
long	get_time_in_ms(void)
{
	struct timeval	tv;
	long	actual_time;

	if (gettimeofday(&tv, NULL) != 0) //on recupere le temps actuel
		return(-1);
	actual_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000); //convertit en millisec
	return(actual_time);
}