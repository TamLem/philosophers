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

#include "philo.h"

int	init_params(t_philos *philos, int argc, char *argv[])
{
	int	i;
	int	num_of_meals;

	i = 0;
	num_of_meals = UNLIMITED;
	if (argc < 5 || argc > 6)
		return (0);
	if ((philos->num_of_philos = ft_atoi(argv[1])) == -1)
		return (0);
	if ((philos->time_to_die = ft_atoi(argv[2])) == -1)
		return (0);
	if ((philos->time_to_eat = ft_atoi(argv[3])) == -1)
		return (0);
	if ((philos->time_to_sleep = ft_atoi(argv[4])) == -1)
		return (0);
	if (argc == 6 && (num_of_meals = ft_atoi(argv[5])) == -1)
		return (0);
	if ((philos->num_meals = malloc(philos->num_of_philos * sizeof(int))) == NULL)
		return (0);
	if ((philos->last_meal = malloc(philos->num_of_philos * sizeof(int))) == NULL)
		return (0);
	while (i < philos->num_of_philos)
	{
		philos->num_meals[i] = num_of_meals;
		philos->last_meal[i] = 0;
		i++;
	}
	philos->tot_num_meals = philos->num_of_philos * num_of_meals;
	philos->started = 0;
	philos->print_lock = philos->num_of_philos;
	philos->shared_lock = philos->print_lock + 1;
	return (1);
}

int	main(int argc, char *argv[])
{
	int			i;
	pthread_t	*threads;
	pthread_t	death_t;
	t_philos	philos;

	i = 0;
	if (!init_params(&philos, argc, argv))
	{
		printf("error: input\n");
		return (1);
	}
	if ((threads = malloc(sizeof(pthread_t) * (philos.num_of_philos))) == NULL)
		return (1);
	if ((philos.mutexs = malloc(sizeof(pthread_mutex_t) * (philos.num_of_philos + 2))) == NULL)
		return (1);
	while (i < philos.num_of_philos + 2)
		pthread_mutex_init(&philos.mutexs[i++], NULL);
	i = 0;
	while (i < philos.num_of_philos)
	{
		gettimeofday(&philos.prog_time, NULL);
		pthread_create(&threads[i], NULL, (void *)life_routine, (void *)&philos);
		// philos.started++;
		i++;
	}
	pthread_create(&death_t, NULL, (void *)death_routine, (void *)&philos);
	i = philos.num_of_philos;
	pthread_join(death_t, NULL);
	while (i > 0)
		pthread_detach(threads[--i]);
	i = 0;
	while (i < philos.num_of_philos + 2)
		pthread_mutex_destroy(&philos.mutexs[i++]);
	return (0);
}
