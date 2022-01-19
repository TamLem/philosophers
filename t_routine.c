/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_routine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:55:29 by tlemma            #+#    #+#             */
/*   Updated: 2022/01/18 23:40:18 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_left_fork(int philo_id,t_philos *philos)
{
	if (philos->num_of_philos == 2)
		return (0);
	return (shift(philo_id));
}

static int	get_right_fork(int philo_id, t_philos *philos)
{
	if (philos->num_of_philos == 2)
		return (1);
	return (philo_id % philos->num_of_philos);
}

int	lock(int to_lock, t_philos *philos)
{
	return (pthread_mutex_lock(&philos->mutexs[to_lock]));
}

int	unlock(int to_lock, t_philos *philos)
{
	return (pthread_mutex_unlock(&philos->mutexs[to_lock]));
}

int	print_status(int status, int philo_id, t_philos *philos)
{
	int	time;

	lock(philos->print_lock, philos);
	time = get_time_ms(philos);
	if (status == FORK)
		printf("%3dms %d has taken a fork\n", time, philo_id);
	if (status == EAT)
		printf("%3dms %d is  eating\n", time, philo_id);
	if (status == SLEEP)
		printf("%3dms %d is  sleeping\n", time, philo_id);
	if (status == THINK)
		printf("%3dms %d is  thinking\n", time, philo_id);
	if (status == DIED)
		printf("%3dms %d has  died\n", time, philo_id);
	unlock(philos->print_lock, philos);
	return (1);
}

int	philo_eat(int philo_id, t_philos *philos)
{
	int	left_fork;
	int	right_fork;

	left_fork = get_left_fork(philo_id, philos);
	right_fork = get_right_fork(philo_id, philos);
	lock(left_fork, philos);
	print_status(FORK, philo_id, philos);
	if (philos->num_of_philos < 2)
	{
		unlock(left_fork, philos);
		return (0);
	}
	lock(right_fork, philos);
	print_status(FORK, philo_id, philos);
	print_status(EAT, philo_id, philos);
	lock(philos->shared_lock, philos);
	philos->last_meal[shift(philo_id)] = get_time_ms(philos);
	if (philos->num_meals[shift(philo_id)] != -1)
	{
		philos->num_meals[shift(philo_id)]--;
		philos->tot_num_meals--;
	}
	unlock(philos->shared_lock, philos);
	ft_usleep(philos->time_to_eat, philos);
	unlock(left_fork, philos);
	unlock(right_fork, philos);
	return (1);
}

int check_death(t_philos *philos)
{
	int	res;

	res = 0;
	lock(philos->shared_lock, philos);
		if (philos->philo_died)
			res = 1;
	unlock(philos->shared_lock, philos);
	return (res);
}

int	life_routine(t_philos *philos)
{
	int	philo_id;

	lock(philos->shared_lock, philos);
		philo_id = 1 + philos->started++;
	unlock(philos->shared_lock, philos);
	if (philo_id % 2 != 0)
		usleep(100);
	while (philos->num_of_philos > 0 && !check_death(philos)) 
	{
		// printf("philo %d meals left %d\n", philo_id, philos->num_meals[shift(philo_id)]);
		if (!philo_eat(philo_id, philos) || philos->num_meals[shift(philo_id)] == 0)
				return 0;
		if (check_death(philos))
			return 0;
		print_status(SLEEP, philo_id, philos);
		ft_usleep(philos->time_to_sleep, philos);
		if (check_death(philos))
			return 0;
		print_status(THINK, philo_id, philos);
	}
	return (1);
}
