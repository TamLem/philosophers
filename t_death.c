/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_death.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:55:37 by tlemma            #+#    #+#             */
/*   Updated: 2022/01/18 23:47:14 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_routine(t_philos *philos)
{
	int	i;

	i = 1;
	// usleep(100);
	while (1)
	{
		lock(shift(i), philos);
		if (philos->tot_num_meals == 0)
			return (1);
		// printf("time %d last_meal %d, time_to_die%d\n", get_time_ms(philos), philos->last_meal[shift(i)], philos->time_to_die);
		if (get_time_ms(philos) - philos->last_meal[shift(i)]
			> philos->time_to_die && philos->num_meals[shift(i)] > 0)
		{
			printf("%3dms %d has  died, meals left %d\n", get_time_ms(philos), i, philos->num_meals[shift(i)]);
			return (1);
		}
		unlock(shift(i), philos);
		i = (i % philos->num_of_philos) + 1;
	}
	return (0);
}
