/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_condition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:57:24 by lezard            #+#    #+#             */
/*   Updated: 2023/11/10 13:54:55 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

int	check_status(t_table *table)
{
	pthread_mutex_lock(&table->m_status);
	if (table->status == 1)
	{
		pthread_mutex_unlock(&table->m_status);
		return (1);
	}
	else if (table->status == 2)
	{
		pthread_mutex_unlock(&table->m_status);
		return (2);
	}
	pthread_mutex_unlock(&table->m_status);
	return (0);
}

int	is_dead(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->m_time_eating);
	if (actual_time() - philo->time_last_meal >= table->time_to_die)
	{
		pthread_mutex_unlock(&table->m_time_eating);
		show_what_philo_do(table, philo, "died");
		pthread_mutex_lock(&table->m_status);
		table->status = ONE_DIED;
		pthread_mutex_unlock(&table->m_status);
		return (1);
	}
	pthread_mutex_unlock(&table->m_time_eating);
	return (0);
}

static int	all_ate(t_table *table)
{
	pthread_mutex_lock(&table->m_check_meal);
	if (table->nb_finish == table->nb_philo)
	{
		pthread_mutex_unlock(&table->m_check_meal);
		pthread_mutex_lock(&table->m_status);
		table->status = ALL_EAT;
		pthread_mutex_unlock(&table->m_status);
		return (1);
	}
	pthread_mutex_unlock(&table->m_check_meal);
	return (0);
}

static int	end_program(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			return (printf("error pthread_join\n"), 1);
		i++;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->philos[i].fork_l);
		i++;
	}
	pthread_mutex_destroy(&table->m_status);
	pthread_mutex_destroy(&table->m_print);
	pthread_mutex_destroy(&table->m_time_eating);
	if (table->status == 2)
		printf("Each philosopher ate %ld time(s)\n", table->nb_must_eat);
	return (0);
}

int	stop_condition(t_table *table)
{
	int	i;

	while (1)
	{
		usleep(100);
		i = 0;
		while (i < table->nb_philo)
		{
			all_ate(table);
			is_dead(table, &table->philos[i]);
			pthread_mutex_lock(&table->m_status);
			if (table->status != 0)
			{
				pthread_mutex_unlock(&table->m_status);
				end_program(table);
				return (0);
			}
			pthread_mutex_unlock(&table->m_status);
			i++;
		}
	}
	return (0);
}
