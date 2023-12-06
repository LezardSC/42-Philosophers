/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:34:34 by jrenault          #+#    #+#             */
/*   Updated: 2023/11/10 13:35:31 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

void	release_fork(t_table *table, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(&philo->fork_l);
		(void)table;
	}
	if (table->nb_philo % 2 == 1 && philo->id % 2 == 0)
		usleep((table->time_to_eat * 0.9) * 700);
	if (table->nb_philo % 2 == 1 && philo->id % 2 == 1)
		usleep((table->time_to_eat * 0.9) * 600);
}

void	take_forks(t_table *table, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_l);
		show_what_philo_do(table, philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_r);
		show_what_philo_do(table, philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_r);
		show_what_philo_do(table, philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork_l);
		show_what_philo_do(table, philo, "has taken a fork");
	}
}
