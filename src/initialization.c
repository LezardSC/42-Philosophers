/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:14:17 by lezard            #+#    #+#             */
/*   Updated: 2023/11/10 13:56:21 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

static void	init_mutex(t_table *table)
{
	pthread_mutex_init(&table->m_print, NULL);
	pthread_mutex_init(&table->m_status, NULL);
	pthread_mutex_init(&table->m_time_eating, NULL);
	pthread_mutex_init(&table->m_check_meal, NULL);
}

static int	init_table(t_table *table)
{
	table->time_to_start = actual_time();
	table->nb_finish = 0;
	table->status = 0;
	return (0);
}

int	initialization(t_table *table)
{
	int	i;

	i = 0;
	init_mutex(table);
	if (init_table(table) == 1)
		return (1);
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		return (error_message("malloc error"), 1);
	while (i < table->nb_philo)
	{
		table->philos[i].nb_meals_eaten = 0;
		table->philos[i].time_last_meal = table->time_to_start;
		table->philos[i].v_table = (void *)table;
		table->philos[i].id = i + 1;
		table->philos[i].dead = 0;
		pthread_mutex_init(&(table->philos[i].fork_l), NULL);
		table->philos[i].fork_r = NULL;
		if (table->nb_philo != 1 && table->philos[i].id != table->nb_philo)
			table->philos[i].fork_r = &(table->philos[i + 1].fork_l);
		else if (table->nb_philo != 1)
			table->philos[i].fork_r = &(table->philos[0].fork_l);
		i++;
	}
	return (0);
}
