/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:43:16 by camerico          #+#    #+#             */
/*   Updated: 2025/04/25 16:51:50 by camerico         ###   ########.fr       */
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
	free_all(&data);
	return(0);
}


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