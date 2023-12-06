/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:09:39 by lezard            #+#    #+#             */
/*   Updated: 2023/11/10 13:56:31 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define ONE_DIED 1
# define ALL_EAT 2
# define AVAILABLE 0
# define TAKEN 1

typedef struct s_philosopher
{
	void			*v_table;
	pthread_t		thread;
	int				id;
	int				dead;
	long int		time_last_meal;
	long int		nb_meals_eaten;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	fork_l;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	long int		nb_philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		nb_must_eat;
	long int		time_to_start;
	long int		nb_finish;
	int				status;
	pthread_mutex_t	m_status;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_time_eating;
	pthread_mutex_t	m_check_meal;
}	t_table;

int			main(int argc, char **argv);
int			check_error(int nb_args, char **argv);
int			parsing(t_table *table, int argc, char **argv);
int			initialization(t_table *table);
int			threading(t_table *table);
void		take_forks(t_table *table, t_philo *philo);
void		release_fork(t_table *table, t_philo *philo);
int			is_dead(t_table *table, t_philo *philo);
int			check_status(t_table *table);
int			stop_condition(t_table *table);

//utils
int			error_message(char *error_message);
void		ft_putstr_fd(char *s, int fd);
int			ft_strlen(char *str);
int			ft_atoi(const char *str, int *error);
long int	actual_time(void);
void		ft_usleep(long int time_in_ms);
void		show_what_philo_do(t_table *table, t_philo *philo, char *str);

#	endif