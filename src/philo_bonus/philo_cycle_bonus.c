/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnubia <rnubia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 09:48:27 by rnubia            #+#    #+#             */
/*   Updated: 2022/07/10 11:58:29 by rnubia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"

static t_bool	philo_thinking(t_philo *philo, t_timeval *time_to_wait)
{
	t_timeval	curr_time;
	t_exist		*exist;

	gettimeofday(&curr_time, NULL);
	exist = philo->exist;
	philo_log(exist, philo, "is thinking", &curr_time);
	if (time_to_wait != NULL)
		usleep_till(philo, time_to_wait);
	sem_wait(exist->forks);
	gettimeofday(&curr_time, NULL);
	philo_log(exist, philo, "has taken a fork", &curr_time);
	if (exist->philo_count != 1)
		sem_wait(exist->forks);
	gettimeofday(&philo->last_eating, NULL);
//	sem_wait(philo->tcheck);
	philo->time_to_die = time_add(&philo->last_eating, exist->time_to_die);
//	sem_post(philo->tcheck);


/*	if (check_death(philo) == true)
	{
		if (exist->philo_count != 1)
			pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}*/
	return (true);
}

static t_bool	philo_eating(t_philo *philo)
{
	t_timeval	time_to_eat;
	t_exist		*exist;

	exist = philo->exist;
	if (exist->philo_count != 1)
		philo_log(exist, philo, "has taken a fork", &philo->last_eating);
	philo_log(exist, philo, "is eating", &philo->last_eating);
	time_to_eat = time_add(&philo->last_eating, exist->time_to_eat - TIMER / 2);
	usleep_till(philo, &time_to_eat);
	if (exist->philo_count != 1)
		sem_post(exist->forks);
	sem_post(exist->forks)
	return (true);
}

static t_bool	philo_sleeping(t_philo *philo)
{
	t_timeval	time_to_sleep;
	t_timeval	curr_time;
	t_exist		*exist;

	gettimeofday(&curr_time, NULL);
	exist = philo->exist;
	philo_log(exist, philo, "is sleeping", &curr_time) == false)
	time_to_sleep = time_add(&philo->last_eating,
			exist->time_to_eat + exist->time_to_sleep - TIMER / 2);
	usleep_till(philo, &time_to_sleep);
	return (true);
}

static	t_bool	philo_ready(t_exist *exist, t_philo *philo)
{
	t_timeval	time_to_wait;
	long long	wait;

	gettimeofday(&philo->last_eating, NULL);
//	sem_wait(philo->tcheck);
	philo->time_to_die = time_add(&philo->last_eating, exist->time_to_die);
//	sem_post(philo->tcheck);
	wait = (exist->time_to_eat / (exist->philo_count / 2))
		* (philo->phid / 2) - TIMER / 2;
	if (exist->philo_count > 1 && exist->philo_count % 2 != 0
		&& philo->phid % 2 == 1)
	{
		time_to_wait = time_add(&exist->inception, wait);
		return (philo_thinking(philo, &time_to_wait));
	}
	if (philo->phid % 2 == 0)
	{
		wait = wait * (exist->philo_count % 2) + exist->time_to_eat;
		time_to_wait = time_add(&exist->inception, wait);
		return (philo_thinking(philo, &time_to_wait));
	}
	return (philo_thinking(philo, NULL));
}

void	*philo_cycle(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo_ready(philo->exist, philo) == false)
		return (NULL);
	while (42)
	{
		if (philo_eating(philo) == true)
		{
			if (++ philo->eating_count == philo->exist->eating_times)
			{
//				sem_wait(philo->echeck);
				philo->exist->eaten = true;
//				sem_post(philo->echeck);
				break ;
			}
			if (philo_sleeping(philo) == false)
				break ;
			if (philo_thinking(philo, NULL) == false)
				break ;
		}
		else
			break ;
	}
	return (NULL);
}
