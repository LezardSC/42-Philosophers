/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:53:24 by lezard            #+#    #+#             */
/*   Updated: 2023/11/10 13:56:27 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

int	check_error(int nb_args, char **argv)
{
	int	i;
	int	j;

	if (nb_args < 4 || nb_args > 5)
		return (1);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	if (i > 10)
		return (1);
	return (0);
}

int	parsing(t_table *table, int argc, char **argv)
{
	int	error;

	error = 0;
	table->nb_philo = ft_atoi(argv[1], &error);
	if (error || table->nb_philo == 0)
		return (1);
	table->time_to_die = ft_atoi(argv[2], &error);
	if (error)
		return (1);
	table->time_to_eat = ft_atoi(argv[3], &error);
	if (error)
		return (1);
	table->time_to_sleep = ft_atoi(argv[4], &error);
	if (error)
		return (1);
	if (argc == 6)
	{
		table->nb_must_eat = ft_atoi(argv[5], &error);
		if (error)
			return (1);
	}
	else
		table->nb_must_eat = -1;
	return (0);
}
