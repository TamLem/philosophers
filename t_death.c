#include "philo.h"

int	death_routine(t_philos *philos)
{
	int	i;

	i = 1;
    while (1)
    {
        // usleep(100);
        if (i == philos->num_of_philos)
            i = 1;
		if (philos->tot_num_meals == 0)
			return (1);
		if (get_time_ms(philos) - philos->last_meal[i] > philos->time_to_die)
		{
			printf("%3dms %d has  died\n", get_time_ms(philos), i + 1);
			exit (-1);
			return (1);
		}
		i++;
    }
	return (0);
}
