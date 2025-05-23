/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:43:16 by camerico          #+#    #+#             */
/*   Updated: 2025/05/22 21:00:26 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		check_arg(argc, argv);
		init_struct(argv, &data, argc);
		creation_mutex(&data);
		init_philo_tab(&data);
		creation_threads(&data);
		while (i < data.nb_of_philo)
		{
			pthread_join(data.philo[i].thread, NULL);
			i++;
		}
		if (data.nb_of_philo > 1)
			pthread_join(data.monitor_thread, NULL);
		free_all(&data);
	}
	else
		ft_exit_error("Wrong number of arguments", NULL);
	return (0);
}
