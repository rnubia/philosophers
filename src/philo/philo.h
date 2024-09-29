/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnubia <rnubia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:51:09 by rnubia            #+#    #+#             */
/*   Updated: 2022/07/09 15:56:37 by rnubia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1

# define ARGS_COUNT	5

# define TIMER	1021

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;
typedef struct s_exist	t_exist;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_philo
{
	pthread_t	ptid;
	int			phid;
	int			eating_count;
	t_timeval	last_eating;
	t_timeval	time_to_die;
	t_mutex		*right_fork;
	t_mutex		*left_fork;
	t_mutex		tcheck;
	t_mutex		dcheck;
	t_bool		death;
	t_exist		*exist;
}	t_philo;

struct s_exist
{
	int			philo_count;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	int			eating_times;
	t_timeval	inception;
	t_philo		*philos;
	t_mutex		*forks;
	t_mutex		lprint;
	t_mutex		echeck;
	t_bool		eaten;
};

t_bool		existence_init(t_exist *exist, int *args);
void		existence_destroy(t_exist *exist);
void		destroy_mutexes(t_exist *exist);

void		*philo_cycle(void *data);

t_bool		check_death(t_philo *philo);
t_bool		check_eatings(t_exist *exist);
t_bool		philo_log(t_exist *exist, t_philo *philo, char *mess,
				t_timeval *time);
void		philo_died(t_exist *exist, t_philo *philo_died, t_timeval *time);

long long	time_sub(t_timeval *min, t_timeval *sub);
t_timeval	time_add(t_timeval *time, long long add_us);
t_bool		time_less(t_timeval *time1, t_timeval *time2);
t_bool		usleep_till(t_philo *philo, t_timeval *time);

#endif
