/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:30:10 by tlemma            #+#    #+#             */
/*   Updated: 2022/01/15 18:04:09 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int number_of_philosophers = 5;
int time_to_die = 800;
int time_to_eat = 200;
int time_to_sleep = 200;
int number_of_times_eat_philosopher_must_eat;
int started;
int last_eat[5];

pthread_mutex_t mutex[5];
struct timeval  prog_time;

int init_params(t_philo params, int argc, char *argv[])
{
    if (argc < 5)
        printf("missing parameters\n");
    int i;

    i = 0;
    while (1)
    {
        
      i++;
    }
    
}

int    get_time_ms(void)
{
    int    time_ms;
    
    struct timeval  thread_time;
    gettimeofday(&thread_time, NULL);
    time_ms = ((thread_time.tv_usec - prog_time.tv_usec) / 1000 ) 
        + ((thread_time.tv_sec - prog_time.tv_sec) * 1000);
    return (time_ms);
}

int    get_time_usec(void)
{
    int    time_usec;
    
    struct timeval  thread_time;
    gettimeofday(&thread_time, NULL);
    time_usec = (thread_time.tv_usec - prog_time.tv_usec) 
        + ((thread_time.tv_sec - prog_time.tv_sec) * 1000000);
    return (time_usec);
}

void ft_usleep(int total_sleep_ms)
{
    int start = get_time_usec();
    total_sleep_ms *= 1000;
    // printf("start %d sleep %d\n", start, total_sleep_ms);
    while (start + total_sleep_ms >= get_time_usec())
        usleep(100);
}

void print_time(void)
{
    printf ("%d ms\n", get_time_ms());
}

int philo_death(int philo_id, char op)
{
    int res = 0;
    
    pthread_mutex_lock(&mutex[philo_id - 1]);
    if (op == 's')
    {
        last_eat[philo_id - 1] = get_time_ms();
        printf("philo %d, started eating at %d\n", philo_id, get_time_ms());
    }
    else
    {
       if (get_time_ms() - last_eat[philo_id - 1] > time_to_die)
       {
            printf("philo %d, now %d, last %d, tte %d\n", philo_id, get_time_ms(), last_eat[philo_id-1], time_to_eat);
           res =  0;
       }
        else
            res = 1;
    }
    pthread_mutex_unlock(&mutex[philo_id - 1]);
    return (res);
}

int     eat(int    philo_id)
{
    pthread_mutex_lock(&mutex[philo_id]);
    // printf("%3dms %d has taken a fork %d\n", get_time_ms(), philo_id, philo_id);
    pthread_mutex_lock(&mutex[philo_id - 1]);
    printf("%3dms %d has taken a fork %d\n", get_time_ms(), philo_id, philo_id - 1);
    printf("%3dms %d is  eating\n", get_time_ms(), philo_id);
    philo_death(philo_id, 's');
    ft_usleep(time_to_eat);
    pthread_mutex_unlock(&mutex[philo_id - 1]);
    pthread_mutex_unlock(&mutex[philo_id]);
    return (1);
}


void    *say_hello(void *prog_time)
{
    struct timeval  thread_time;
    gettimeofday(&thread_time, NULL);
    printf("hello after %d usec\n", thread_time.tv_usec - ((struct timeval *)prog_time)->tv_usec);
    return (NULL);
}

void    routine(int *id)
{
    int philo_id = *id;
    if (philo_id % 2 != 0)
        usleep(100);
    eat(philo_id);
    printf("%3dms %d is  sleeping\n", get_time_ms(), philo_id);
    ft_usleep(time_to_sleep);
    printf("%3dms %d is  thinking\n", get_time_ms(), philo_id);
    pthread_exit(NULL);
}

int main(void)
{
    int             i;
    pthread_t       threads[number_of_philosophers];
    int             philo_id[number_of_philosophers];

    i = 0;
    while (i++ < number_of_philosophers)
        pthread_mutex_init(&mutex[i], NULL);
    i = 0;
    started = 0;
    while (i <= number_of_philosophers)
    {
        gettimeofday(&prog_time, NULL);
        philo_id[i] = i + 1;
        if (i == 0)
            pthread_create(&threads[i], NULL, (void *)philo_death, (void *)&philo_id[i]);
        else
            pthread_create(&threads[i], NULL, (void *)routine, (void *)&philo_id[i]);
        i++;
    }
    i = 1;
    while (1)
    {
        ft_usleep(105);
        if (!philo_death(i, 'g'))
        {
            printf("%3dms %d has  died, last %d\n", get_time_ms(), i, last_eat[i]);
            return (0);
        }
        if (i == number_of_philosophers)
            i = 0;
        else
            i++;
    }
    i = number_of_philosophers - 1;
    while (i > 0)
        pthread_join(threads[i--], NULL);
    i = 0;
    while (i < number_of_philosophers)
        pthread_mutex_destroy(&mutex[i++]);
}