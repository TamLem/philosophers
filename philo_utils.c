#include "philo.h"

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
        usleep(10);
}

void print_time(t_philos *philos)
{
    printf ("%d ms\n", get_time_ms(philos));
}
