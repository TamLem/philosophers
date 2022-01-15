/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:30:10 by tlemma            #+#    #+#             */
/*   Updated: 2022/01/15 19:40:33 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_params(t_philos *philos, int argc, char *argv[])
{
    int i;
	int num_of_meals;

	i = 0;
    if (argc < 5)
        return (0);
	if ((philos->num_of_philos = ft_atoi(argv[1])) == 0)
		return (0);	
	if ((philos->time_to_die = ft_atoi(argv[2])) == 0)
		return (0);
	if ((philos->time_to_eat = ft_atoi(argv[3])) == 0)
		return (0);
	if ((philos->time_to_sleep = ft_atoi(argv[4])) == 0)
		return (0);
	if ((num_of_meals = ft_atoi(argv[5])) == 0)
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
	philos->started = 0;
	return (1);
}

int    get_time_ms(t_philos *philos)
{
    int    time_ms;
    
    struct timeval  thread_time;
    gettimeofday(&thread_time, NULL);
    time_ms = ((thread_time.tv_usec - philos->prog_time.tv_usec) / 1000 ) 
        + ((thread_time.tv_sec - philos->prog_time.tv_sec) * 1000);
    return (time_ms);
}

int    get_time_usec(t_philos *philos)
{
    int    time_usec;
    
    struct timeval  thread_time;
    gettimeofday(&thread_time, NULL);
    time_usec = (thread_time.tv_usec - philos->prog_time.tv_usec) 
        + ((thread_time.tv_sec - philos->prog_time.tv_sec) * 1000000);
    return (time_usec);
}

void ft_usleep(int total_sleep_ms, t_philos *philos)
{
    int start = get_time_usec(philos);
    total_sleep_ms *= 1000;
    // printf("start %d sleep %d\n", start, total_sleep_ms);
    while (start + total_sleep_ms >= get_time_usec(philos))
        usleep(100);
}

void print_time(t_philos *philos)
{
    printf ("%d ms\n", get_time_ms(philos));
}

int	philo_eat(int philo_id, t_philos *philos)
{
    pthread_mutex_lock(&philos->mutex[philo_id]);
    // printf("%3dms %d has taken a fork %d\n", get_time_ms(), philo_id, philo_id);
    printf("%3dms %d has taken a fork %d\n", get_time_ms(philos), philo_id, philo_id - 1);
    printf("%3dms %d is  eating\n", get_time_ms(philos), philo_id);
    philos->last_meal[philo_id - 1] = get_time_ms(philos);
    ft_usleep(philos->time_to_eat, philos);
    pthread_mutex_unlock(&philos->mutex[philo_id - 1]);
    pthread_mutex_unlock(&philos->mutex[philo_id]);
    return (1);
}


void    *say_hello(void *prog_time)
{
    struct timeval  thread_time;
    gettimeofday(&thread_time, NULL);
    printf("hello after %d usec\n", thread_time.tv_usec - ((struct timeval *)prog_time)->tv_usec);
    return (NULL);
}

void    routine(t_philos *philos)
{
    int	philo_id;

	philo_id = philos->started++ + 1;
    if (philo_id % 2 != 0)
        usleep(100);
    philo_eat(philo_id, philos);
    printf("%3dms %d is  sleeping\n", get_time_ms(philos), philo_id);
    ft_usleep(philos->time_to_sleep, philos);
    printf("%3dms %d is  thinking\n", get_time_ms(philos), philo_id);
    pthread_exit(NULL);
}

int	death(t_philos *philos)
{
	int	i;

	i = 1;
    while (1)
    {
        ft_usleep(105, philos);
		if (get_time_ms(philos) - philos->last_meal[i] > philos->time_to_die)
		{
			printf("%3dms %d has  died\n", get_time_ms(philos), i + 1);
			exit (1);
		}
        if (i == philos->num_of_philos)
            i = 0;
		i++;
    }
}

int main(int argc, char *argv[])
{
    int             i;
    pthread_t       *threads;
	pthread_t		*death_t;
	t_philos		philos;

    i = 0;
	if (!init_params(&philos, argc, argv))
		return (1);
	if ((threads = malloc(sizeof(pthread_t) * philos.num_of_philos)) == NULL)
		return (1);
	if ((philos.mutex = malloc(sizeof(pthread_mutex_t) * philos.num_of_philos)) == NULL)
		return (1);
    while (i < philos.num_of_philos)
        pthread_mutex_init(&philos.mutex[i++], NULL);
    i = 0;
    while (i < philos.num_of_philos)
    {
        gettimeofday(&philos.prog_time, NULL);
		pthread_create(&threads[i], NULL, (void *)routine, (void *)&philos);
        i++;
    }
	death_t = malloc(sizeof(pthread_t));
	pthread_create(death_t, NULL, (void *)death, (void *)&philos);

    while (i > 0)
        pthread_join(threads[i--], NULL);

	pthread_join(*death_t, NULL);
    i = 0;
    while (i < philos.num_of_philos)
        pthread_mutex_destroy(&philos.mutex[i++]);
}