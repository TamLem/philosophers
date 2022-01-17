#include "philo.h"

int	get_left_fork(int philo_id, t_philos *philos)
{
	return (philo_id - 1);
}

int	get_right_fork(int philo_id, t_philos *philos)
{
	if (philo_id == philos->num_of_philos)
		return (0);
	return (philo_id);
}

int	philo_eat(int philo_id, t_philos *philos)
{
	int	left_fork = get_left_fork(philo_id, philos);
	int	right_fork = get_right_fork(philo_id, philos);

    pthread_mutex_lock(&philos->mutex[left_fork]);
    printf("%3dms %d has taken a fork %d\n", get_time_ms(philos), philo_id, philo_id);
    pthread_mutex_lock(&philos->mutex[right_fork]);
    printf("%3dms %d has taken a fork %d\n", get_time_ms(philos), philo_id, philo_id - 1);
    printf("%3dms %d is  eating\n", get_time_ms(philos), philo_id);
    philos->last_meal[philo_id - 1] = get_time_ms(philos);
	if (philos->num_meals[philo_id - 1] != -1)
    	philos->num_meals[philo_id - 1]--;
    ft_usleep(philos->time_to_eat, philos);
    pthread_mutex_unlock(&philos->mutex[left_fork]);
    pthread_mutex_unlock(&philos->mutex[right_fork]);
    return (1);
}

void    routine(t_philos *philos)
{
    int	philo_id;
    int i;

    i = 0;
	philo_id = 1 + philos->started++;
    if (philo_id % 2 != 0)
        usleep(100);
    while (philos->num_meals[philo_id - 1] > 0|| philos->num_meals[i] == -1)
    {
        philo_eat(philo_id, philos);
        printf("%3dms %d is  sleeping\n", get_time_ms(philos), philo_id);
        ft_usleep(philos->time_to_sleep, philos);
        printf("%3dms %d is  thinking\n", get_time_ms(philos), philo_id);
    }
    pthread_exit(NULL);
}