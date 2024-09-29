/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnubia <rnubia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 09:22:48 by rnubia            #+#    #+#             */
/*   Updated: 2022/07/10 11:43:17 by rnubia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <sys/time.h>

# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1

# define ARGS_COUNT	5

# define TIMER	1021

typedef struct timeval	t_timeval;
typedef struct s_exist	t_exist;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_philo
{
	int			phid;
	int			eating_count;
	t_timeval	last_eating;
	t_timeval	time_to_die;
	pthread_t	dmon;
	sem_t		*tcheck;
	sem_t		*echeck;
	t_bool		death;
	t_bool		eaten;///
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
	pid_t		*pids;
	sem_t		*forks;
	sem_t		*lprint;
};

t_bool		existence_init(t_exist *exist, int *args);
void		existence_destroy(t_exist *exist);

void		*philo_cycle(void *data);

t_bool		check_death(t_exist *exist);
t_bool		check_eatings(t_philo *philo);
t_bool		philo_log(t_exist *exist, t_philo *philo, char *mess,
				t_timeval *time);
void		philo_died(t_exist *exist, t_philo *philo, t_timeval *time);

long long	time_sub(t_timeval *min, t_timeval *sub);
t_timeval	time_add(t_timeval *time, long long add_us);
t_bool		time_less(t_timeval *time1, t_timeval *time2);
void		usleep_till(t_timeval *time);

#endif
