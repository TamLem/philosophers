/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:11:26 by tlemma            #+#    #+#             */
/*   Updated: 2022/01/20 14:52:12 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_death(t_philos *philos)
{
	int	res;

	res = 0;
	lock(philos->shared_lock, philos);
	if (philos->philo_died)
		res = 1;
	unlock(philos->shared_lock, philos);
	return (res);
}

int	lock(int to_lock, t_philos *philos)
{
	return (pthread_mutex_lock(&philos->mutexs[to_lock]));
}

int	unlock(int to_lock, t_philos *philos)
{
	return (pthread_mutex_unlock(&philos->mutexs[to_lock]));
}

int	shift(int index)
{
	return (index - 1);
}

int	print_status(int status, int philo_id, t_philos *philos)
{
	int	time;
	int	philo_died;

	philo_died = 0;
	lock(philos->shared_lock, philos);
	philo_died = philos->philo_died;
	unlock(philos->shared_lock, philos);
	time = get_time_ms(philos);
	if (status == DIED)
		printf("%3dms  %3d   has    died\n", time, philo_id);
	if (status == FORK && !philo_died)
		printf("%3dms  %3d   has   taken a fork\n", time, philo_id);
	if (status == EAT && !philo_died)
		printf("%3dms  %3d   is    eating\n", time, philo_id);
	if (status == SLEEP && !philo_died)
		printf("%3dms  %3d   is    sleeping\n", time, philo_id);
	if (status == THINK && !philo_died)
		printf("%3dms  %3d   is    thinking\n", time, philo_id);
	return (1);
}
