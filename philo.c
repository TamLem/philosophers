/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:30:10 by tlemma            #+#    #+#             */
/*   Updated: 2022/01/11 22:42:40 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int number_of_philosophers = 5;
int time_to_die = 20;
int time_to_eat = 20;
int time_to_sleep = 20;
int number_of_times_eat_philosopher_must_eat;

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

int ft_usleep(int total_sleep)
{
    int slept;

    slept = 0;
    while (slept <= total_sleep)
    {
        usleep(100);
        // if(sleep(100) == -1)
        //     return (-1);
        slept += 100;
    }
    return (0);
}

int get_time(void)
{
    struct timeval  thread_time;
    gettimeofday(&thread_time, NULL);
    return ((thread_time.tv_usec / 1000 + thread_time.tv_sec * 1000) - 
            (prog_time.tv_usec / 1000 + prog_time.tv_sec * 1000));
}

int     eat(int    philo_id)
{
    pthread_mutex_lock(&mutex[philo_id]);
    pthread_mutex_lock(&mutex[philo_id - 1]);
    printf("%3dms %d has taken a fork\n", get_time(), philo_id);
    printf("%3dms %d is  eating\n", get_time(), philo_id);
    ft_usleep(time_to_eat * 1000);
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
    eat(philo_id);
    printf("%3dms %d is  sleeping\n", get_time(), philo_id);
    ft_usleep(time_to_sleep * 1000);
    printf("%3dms %d is  thinking\n", get_time(), philo_id);
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
    gettimeofday(&prog_time, NULL);
    while (i < number_of_philosophers)
    {
        philo_id[i] = i + 1;
        pthread_create(&threads[i], NULL, (void *)routine, (void *)&philo_id[i]);
        i++;
    }
    while (i > 0)
        pthread_join(threads[i--], NULL);
    i = 0;
    while (i < number_of_philosophers)
        pthread_mutex_destroy(&mutex[i++]);
}