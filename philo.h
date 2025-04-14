/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:09:57 by camerico          #+#    #+#             */
/*   Updated: 2025/04/14 16:10:01 by camerico         ###   ########.fr       */
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
	int	nb_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_meals_required;
	pthread_mutex_t	*fork_mutex;
	pthread_t	*thread;
	t_philo	*philo_tab;
}	t_data;

//struct pour chaque philo
typedef struct s_philo
{
	int	id;
}	t_philo;


/* ************************************************************************** */
/* PROTO                                                                      */
/* ************************************************************************** */

int	ft_atoi(const char *nptr);
void	init_struct(char **argv, t_philo *philo, int argc);
void	creation_mutex(t_philo *philo);
void	creation_threads(t_philo *philo);
void	routine(t_philo *philo);

/* ************************************************************************** */
/* DEBUG                                                                      */
/* ************************************************************************** */

