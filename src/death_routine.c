/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:55:37 by tlemma            #+#    #+#             */
/*   Updated: 2022/01/20 14:52:31 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	death_routine(t_philos *philos)
{
	int	i;
	int	res;

	i = 1;
	res = 1;
	usleep(100);
	while (res)
	{
		lock(philos->shared_lock, philos);
		if (philos->tot_num_meals == 0)
			break ;
		if (get_time_ms(philos) - philos->last_meal[shift(i)]
			> philos->time_to_die && philos->num_meals[shift(i)] != 0)
		{
			philos->philo_died = 1;
			res = 0;
			usleep(1000);
			printf("%3dms  %3d   has    died\n", get_time_ms(philos), i);
		}
		unlock(philos->shared_lock, philos);
		usleep(100);
		i = (i % philos->num_of_philos) + 1;
	}
	return (0);
}
