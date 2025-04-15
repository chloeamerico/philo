/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:09:57 by camerico          #+#    #+#             */
/*   Updated: 2025/04/15 18:09:14 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#endif

/* ************************************************************************** */
/* INCLUDES                                                                   */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>

/* ************************************************************************** */
/* DEFINES                                                                    */
/* ************************************************************************** */

/* ************************************************************************** */
/* STRUCTURES                                                                 */
/* ************************************************************************** */

//struct globale a tous le projet
typedef struct s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_meals_required;
	long			start_time;
	int				philo_death;		// 0 tout va bien, 1 un philo est mort
	pthread_mutex_t	philo_death_mutex;
	pthread_mutex_t	*fork_mutex;
	pthread_t		*thread;
	t_philo			*philo;
}	t_data;

//struct pour chaque philo
typedef struct s_philo
{
	int				id; 				// de 1 a (nb de philo)
	long			last_meal;
	int				meals_count;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;


/* ************************************************************************** */
/* PROTO                                                                      */
/* ************************************************************************** */

int	ft_atoi(const char *nptr);
void	init_struct(char **argv, t_data *data, int argc);
void	creation_mutex(t_data *data);
void	creation_threads(t_data *data);
void	routine(t_data *data);

/* ************************************************************************** */
/* DEBUG                                                                      */
/* ************************************************************************** */

