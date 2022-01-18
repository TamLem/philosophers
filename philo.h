/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   philo.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tlemma <tlemma@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/01/11 16:33:28 by tlemma			#+#	#+#			 */
/*   Updated: 2022/01/18 18:39:23 by tlemma		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

# define UNLIMITED -1
# define FORK   0
# define EAT	1
# define SLEEP  2
# define THINK  3
# define DIED   4

typedef struct s_philos
{
	int				id;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				*num_meals;
	int				tot_num_meals;
	int				*last_meal;
	int				started;
	int				print_lock;
	int				shared_lock;
	pthread_mutex_t	*mutexs;
	struct timeval	prog_time;
}				t_philos;

long	ft_atoi(const char *str);
int		life_routine(t_philos *philos);
int		get_time_ms(t_philos *philos);
int		get_time_usec(t_philos *philos);
void	ft_usleep(int total_sleep_ms, t_philos *philos);
void	print_time(t_philos *philos);
int		death_routine(t_philos *philos);
int		shift(int index);
int		print_status(int status, int philo_id, t_philos *philos);
void	print_params(t_philos *philos);
int		lock(int to_lock, t_philos *philos);
int		unlock(int to_lock, t_philos *philos);

#endif
