/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   philo.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tlemma <tlemma@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/01/11 12:30:10 by tlemma			#+#	#+#			 */
/*   Updated: 2022/01/18 18:43:08 by tlemma		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../include/philo.h"

void	init_rest(t_philos *philos, int num_of_meals)
{
	int	i;

	i = 0;
	while (i < philos->num_of_philos)
	{
		philos->num_meals[i] = num_of_meals;
		philos->last_meal[i] = 0;
		i++;
	}
	philos->started = 0;
	philos->philo_died = 0;
	philos->tot_num_meals = philos->num_of_philos * num_of_meals;
	philos->shared_lock = philos->num_of_philos;
}

int	init_params(t_philos *philos, int argc, char *argv[])
{
	int	num_of_meals;

	if (!check_input(&argv[1]) || argc < 5 || argc > 6)
		return (0);
	num_of_meals = UNLIMITED;
	philos->num_of_philos = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		num_of_meals = ft_atoi(argv[5]);
	philos->num_meals = malloc(philos->num_of_philos * sizeof(int));
	if (philos->num_meals == NULL)
		return (0);
	philos->last_meal = malloc(philos->num_of_philos * sizeof(int));
	if (philos->last_meal == NULL)
		return (0);
	init_rest(philos, num_of_meals);
	return (1);
}

int	start_simulation(pthread_t *philo_threads,
	pthread_t *death_thread, t_philos *philos)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (i < philos->num_of_philos + 1)
		pthread_mutex_init(&philos->mutexs[i++], NULL);
	i = 0;
	while (i < philos->num_of_philos)
	{
		gettimeofday(&philos->prog_time, NULL);
		res = pthread_create(&(philo_threads[i]), NULL,
				(void *)life_routine, (void *)philos);
		i++;
	}
	res = pthread_create(death_thread, NULL,
			(void *)death_routine, (void *)philos);
	return (res);
}

int	main(int argc, char *argv[])
{
	int			i;
	pthread_t	*philo_threads;
	pthread_t	death_thread;
	t_philos	philos;

	if (!init_params(&philos, argc, argv) && printf("error\n"))
		return (1);
	philo_threads
		= malloc(sizeof(pthread_t) * (philos.num_of_philos));
	philos.mutexs
		= malloc(sizeof(pthread_mutex_t) * (philos.num_of_philos + 1));
	if (philo_threads == NULL || philos.mutexs == NULL)
		return (1);
	if (start_simulation(philo_threads, &death_thread, &philos) != 0)
		return (1);
	pthread_join(death_thread, NULL);
	i = philos.num_of_philos;
	while (i > 0)
		pthread_join(philo_threads[--i], NULL);
	i = 0;
	while (i < philos.num_of_philos + 1)
		pthread_mutex_destroy(&philos.mutexs[i++]);
	free(philo_threads);
	free(philos.mutexs);
	return (0);
}
