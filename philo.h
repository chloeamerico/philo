/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:09:57 by camerico          #+#    #+#             */
/*   Updated: 2025/05/23 18:04:45 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
# include <sys/time.h>

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
	int				philo_death;
	pthread_mutex_t	philo_death_mutex;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	start_simulation_mutex;
	pthread_t		monitor_thread;
	struct s_philo	*philo;
}	t_data;

//struct pour chaque philo
typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				meals_count;
	int				full_flag;
	pthread_t		thread;	
	pthread_mutex_t	meals_count_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

/* ************************************************************************** */
/* PROTO                                                                      */
/* ************************************************************************** */

int			check_arg(int argc, char **argv);
int			is_num(char *str);
int			is_limits(char *str);
int			take_fork(t_philo *philo, t_data *data);
int			philo_is_eating(t_philo *philo, t_data *data);
int			philo_is_thinking(t_philo *philo, t_data *data);
int			philo_is_sleeping(t_philo *philo, t_data *data);
int			check_simulation_end(t_data *data);
int			main(int argc, char **argv);
long long	get_time_in_ms(void);
long		ft_atol(char *str);
void		init_struct(char **argv, t_data *data, int argc);
void		creation_mutex(t_data *data);
void		destroy_mutex(int nb_mutex, t_data *data);
void		init_philo_tab(t_data *data);
void		creation_threads(t_data *data);
void		check_if_dead(t_data *data);
void		*monitor(void *arg);
void		free_all(t_data *data);
void		printf_action(t_philo *philo, t_data *data, char *str);
void		*routine(void *philosophe);
void		routine_for_one(t_philo *philo);
void		ft_mutex_init(pthread_mutex_t *mutex, t_data *data);
void		ft_exit_error(char *message, t_data	*data);
void		wait_and_init_routine(t_philo *philo);
int			ft_usleep(long time_to_sleep, t_philo *philo);
int			each_philo_action_routine(t_philo *philo);
void		full_flag(t_philo *philo);
void		decalage_debut_routine(t_data *data, t_philo *philo);

/* ************************************************************************** */
/* DEBUG                                                                      */
/* ************************************************************************** */

#endif