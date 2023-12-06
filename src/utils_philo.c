/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:11:28 by lezard            #+#    #+#             */
/*   Updated: 2023/11/10 13:56:08 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

int	error_message(char *error_message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(error_message, 2);
	return (0);
}

long int	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		error_message("Gettimeofday failed\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

void	show_what_philo_do(t_table *table, t_philo *philo, char *str)
{
	long int	time;

	time = -1;
	time = actual_time() - table->time_to_start;
	pthread_mutex_lock(&table->m_print);
	if ((time >= 0 && time <= INT_MAX) && !check_status(table))
		printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&table->m_print);
}
