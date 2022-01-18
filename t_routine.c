#include "philo.h"

static int	get_left_fork(int philo_id)
{
	return (philo_id - 1);
}
static int	get_right_fork(int philo_id, t_philos *philos)
{
	return (philo_id % philos->num_of_philos);
}

int philo_eat(int philo_id, t_philos *philos)
{
	int	left_fork = get_left_fork(philo_id);
	int	right_fork = get_right_fork(philo_id, philos);

    // printf("left %d right %d\n", left_fork, right_fork);
    pthread_mutex_lock(&philos->mutex[left_fork]);
    printf("%3dms has taken a fork\n", get_time_ms(philos));
    pthread_mutex_lock(&philos->mutex[right_fork]);
    printf("%3dms has taken a fork\n", get_time_ms(philos));
    printf("%3dms %d is  eating\n", get_time_ms(philos), philo_id);
    philos->last_meal[philo_id - 1] = get_time_ms(philos);
	if (philos->num_meals[philo_id - 1] != -1)
    {
    	philos->num_meals[philo_id - 1]--;
        philos->tot_num_meals--;
    }
    ft_usleep(philos->time_to_eat, philos);
    pthread_mutex_unlock(&philos->mutex[left_fork]);
    pthread_mutex_unlock(&philos->mutex[right_fork]);
    return (1);
}

int check_death(int philo_id, t_philos *philos)
{
    if (get_time_ms(philos) - philos->last_meal[philo_id - 1] > philos->time_to_die)
        return (1);
    return (0);
}


int    routine(t_philos *philos)
{
    int	philo_id;

    philo_id = 0;
	philo_id = 1 + philos->started++;
    if (philo_id % 2 != 0)
        usleep(100);
    while (philos->num_of_philos > 1)
    {
        philo_eat(philo_id, philos);
        if (philos->num_meals[philo_id - 1] == 0)
            break ;
        printf("%3dms %d is  sleeping\n", get_time_ms(philos), philo_id);
        ft_usleep(philos->time_to_sleep, philos);
        printf("%3dms %d is  thinking\n", get_time_ms(philos), philo_id);
    }
    return (1);
}