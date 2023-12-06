/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:52:03 by lezard            #+#    #+#             */
/*   Updated: 2023/11/10 13:56:17 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_error(argc - 1, argv) == 1)
		return (error_message("Args are not valid\n"));
	if (parsing(&table, argc, argv) == 1)
		return (error_message("Args are not valid\n"));
	if (initialization(&table) == 1)
		return (1);
	if (threading(&table) == 1)
		return (free(table.philos), 1);
	stop_condition(&table);
	free(table.philos);
	return (0);
}
