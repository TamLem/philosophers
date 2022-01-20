/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:55:29 by tlemma            #+#    #+#             */
/*   Updated: 2022/01/20 16:03:48 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_fork(char fork, int philo_id, t_philos *philos)
{
	if (fork == 'L')
	{
		if (philos->num_of_philos == 2)
			return (0);
		return (shift(philo_id));
	}
	if (philos->num_of_philos == 2)
		return (1);
	return (philo_id % philos->num_of_philos);
}

static void	update_status(int philo_id, t_philos *philos)
{
	lock(philos->shared_lock, philos);
	philos->last_meal[shift(philo_id)] = get_time_ms(philos);
	if (philos->num_meals[shift(philo_id)] != -1)
	{
		philos->num_meals[shift(philo_id)]--;
		philos->tot_num_meals--;
	}
	unlock(philos->shared_lock, philos);
}

static int	philo_eat(int philo_id, t_philos *philos)
{
	int	left_fork;
	int	right_fork;

	left_fork = get_fork('L', philo_id, philos);
	right_fork = get_fork('R', philo_id, philos);
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
	update_status(philo_id, philos);
	ft_usleep(philos->time_to_eat, philos);
	unlock(left_fork, philos);
	unlock(right_fork, philos);
	return (1);
}

void	buffer_threads(int philo_id, t_philos *philos)
{
	int	res;

	res = 1;
	while (res)
	{
		lock(philos->shared_lock, philos);
		if (philos->num_of_philos == philos->started)
			res = 0;
		unlock(philos->shared_lock, philos);
		usleep(10);
	}
	if (philo_id % 2 != 0)
		usleep(30000);
}

int	life_routine(t_philos *philos)
{
	int	philo_id;

	lock(philos->shared_lock, philos);
	philo_id = 1 + philos->started++;
	unlock(philos->shared_lock, philos);
	buffer_threads(philo_id, philos);
	while (philos->num_of_philos > 0 && !check_death(philos))
	{
		if (!philo_eat(philo_id, philos)
			|| philos->num_meals[shift(philo_id)] == 0)
			return (0);
		if (check_death(philos))
			return (0);
		print_status(SLEEP, philo_id, philos);
		ft_usleep(philos->time_to_sleep, philos);
		if (check_death(philos))
			return (0);
		print_status(THINK, philo_id, philos);
	}
	return (1);
}
