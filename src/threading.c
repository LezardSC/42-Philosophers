/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:14:19 by lezard            #+#    #+#             */
/*   Updated: 2023/11/10 13:55:54 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

static int	philo_alone(t_table *table, t_philo *philo)
{
	if (table->nb_philo == 1)
	{
		show_what_philo_do(table, philo, "has taken a fork");
		ft_usleep(table->time_to_die);
		return (1);
	}
	return (0);
}

static void	sleep_think(t_table *table, t_philo *philo)
{
	show_what_philo_do(table, philo, "is sleeping");
	ft_usleep(table->time_to_sleep);
	show_what_philo_do(table, philo, "is thinking");
}

static void	philo_eat(t_table *table, t_philo *philo)
{
	if (philo_alone(table, philo) == 1)
		return ;
	take_forks(table, philo);
	show_what_philo_do(table, philo, "is eating");
	pthread_mutex_lock(&table->m_time_eating);
	philo->time_last_meal = actual_time();
	pthread_mutex_unlock(&table->m_time_eating);
	philo->nb_meals_eaten++;
	pthread_mutex_lock(&table->m_check_meal);
	if (table->nb_must_eat != -1
		&& philo->nb_meals_eaten == table->nb_must_eat)
		table->nb_finish++;
	pthread_mutex_unlock(&table->m_check_meal);
	ft_usleep(table->time_to_eat);
	release_fork(table, philo);
	sleep_think(table, philo);
}

void	*routine(void *v_philo)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)v_philo;
	table = (t_table *)philo->v_table;
	pthread_mutex_lock(&table->m_status);
	pthread_mutex_unlock(&table->m_status);
	if (!(philo->id % 2))
		ft_usleep(table->time_to_eat / 10);
	while (!check_status(table))
		philo_eat(table, philo);
	return (NULL);
}

int	threading(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->m_status);
	while (i < table->nb_philo)
	{
		if (pthread_create((&table->philos[i].thread),
				NULL, routine, &table->philos[i]))
			return (1);
		i++;
	}
	pthread_mutex_unlock(&table->m_status);
	return (0);
}
