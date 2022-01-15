/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:33:28 by tlemma            #+#    #+#             */
/*   Updated: 2022/01/15 19:03:14 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>


typedef struct s_philos
{
    int             id;
    int             num_of_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             *num_meals;
    int             *last_meal;
    int             started;
	pthread_mutex_t *mutex;
    _STRUCT_TIMEVAL prog_time;
    
}       t_philos;

long	ft_atoi(const char *str);

#endif
